//
// Created by up on 2020/9/22.
//
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/viz.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include<cv_bridge/cv_bridge.h>

#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include "string"
#include <time.h>
#include <queue>
#include <vector>

#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <chrono>
#include<sstream>

#include<librealsense2/rs.hpp>
#include <csignal>

using namespace std;

/*
 * global variable
 */
geometry_msgs::PoseStamped plane_atti_msg;
geometry_msgs::PoseStamped vision_pose_msg;

cv::Point2i target_left_up;
cv::Point2i target_right_down;
cv::Point2i pickup_left_up;
cv::Point2i pickup_right_down;
int target_width;
int target_height;
bool targetDetectFlag = false;
int id_name;
Eigen::Vector4d target_position_of_img;
Eigen::Vector4d target_position_of_drone;
Eigen::Vector4d target_position_of_world;
geometry_msgs::Vector3 drone_euler;
geometry_msgs::Vector3 drone_euler_init;
Eigen::Quaterniond drone_quaternion;
Eigen::Vector3d drone_pos_vision;
geometry_msgs::PoseStamped msg_drone_pos_vision;
geometry_msgs::PoseStamped msg_target_pose_from_img;
geometry_msgs::PoseStamped msg_target_pose_world;
bool got_attitude_init = false;

geometry_msgs::Vector3 drone_euler_real;


//param
//uav01
// double cx_color = 338.960065;
// double cy_color = 244.856900;
// double fx_color = 446.8877;
// double fy_color = 446.032355;

//uav02
double cx_color = 341.530207;
double cy_color = 243.635387;
double fx_color = 451.664427;
double fy_color = 450.081841;

Eigen::Isometry3d tf_image_to_enu;
Eigen::Isometry3d tf_camera_to_drone;
Eigen::Isometry3d tf_drone_to_world;
Eigen::Vector3d tf_camera_drone;

//yolo
float target_width_world = 0.30;
float scale_size = 1;
cv::Point2f yolo_center;

std::queue<geometry_msgs::PoseStamped> pose_queue; //飞机姿态的quene
double image_ros_time = 0.0;


// function declarations
void plane_attitude_sub(const geometry_msgs::PoseStamped::ConstPtr& msg);
void vision_pose_sub(const geometry_msgs::PoseStamped::ConstPtr& msg);
void target_corner_sub(const geometry_msgs::PoseStamped::ConstPtr& msg);
void tf_param_set();
void get_init_yaw();
geometry_msgs::Quaternion euler2quaternion(float roll, float pitch, float yaw);
Eigen::Quaterniond euler2quaternion_eigen(float roll, float pitch, float yaw);
geometry_msgs::Vector3 quaternion2euler(float x, float y, float z, float w);

// watchsignal flag
bool flag = true;

void shutdown_handler(int)
{
    cout<<"shutdown"<<endl;
    flag = false;
} 

// capture the signal from keyboard
void watchSignal() {
    signal(SIGINT, shutdown_handler);
    signal(SIGTERM, shutdown_handler);
    signal(SIGKILL, shutdown_handler);
    signal(SIGQUIT, shutdown_handler);
}


//main function
int main(int argc, char **argv) {

    ros::init(argc, argv, "pnp_target_node");
    ros::NodeHandle nh;
    ros::Rate rate(30);

    // 订阅飞机姿态,并存放到quene里
    ros::Subscriber plane_attitude = nh.subscribe<geometry_msgs::PoseStamped>("/uav2/mavros/local_position/pose",1,plane_attitude_sub);
    // 订阅识别目标,如果有将targetDetectFlag置为1，并且根据内参换算出物体相对相机的实际位置
    ros::Subscriber target_corner = nh.subscribe<geometry_msgs::PoseStamped>("yolo_target_corner",1,target_corner_sub);
    // vision_pose
    ros::Subscriber vision_pose = nh.subscribe<geometry_msgs::PoseStamped>("/uav2/mavros/vision_pose/pose",1,vision_pose_sub);
    // 物体相对相机的位置
    ros::Publisher msg_target_pose_from_img_pub = nh.advertise<geometry_msgs::PoseStamped>("topic_target_pose_from_img",1);
    // 物体相对飞机的最终位置
    ros::Publisher drone_pos_vision_pub = nh.advertise<geometry_msgs::PoseStamped>("drone_pos_vision",1);
    // target pose to the world
    ros::Publisher target_pose_world_pub = nh.advertise<geometry_msgs::PoseStamped>("target_pose_world",1);


    //tf 参数设置
    tf_param_set();

    //ros::duration
    cout << "Start Ros Duration" << endl;
    ros::Duration(5).sleep();
    cout << "End Ros Duration" << endl;

    //获取初始飞机姿态
    while (! got_attitude_init){
        ros::spinOnce();
        ROS_INFO("getting yaw init ... ");
        //git initial yaw
        get_init_yaw(); 
        rate.sleep();
    }


    while(ros::ok() && flag){
        // check if there is signal input from the keyboard
        watchSignal();

         ros::spinOnce();//执行一次回调
         if(!targetDetectFlag){
             //修改标志位
             msg_target_pose_from_img.header.stamp = ros::Time::now();
             msg_target_pose_from_img.pose.position.z = 0;
             msg_target_pose_from_img.pose.position.x = 0;
             msg_target_pose_from_img.pose.position.y = 0;
             msg_target_pose_from_img.pose.orientation.w = -1000;
             //修改标志位
             msg_drone_pos_vision.header.stamp = ros::Time::now();
             msg_drone_pos_vision.pose.position.z = 0;
             msg_drone_pos_vision.pose.position.x = 0;
             msg_drone_pos_vision.pose.position.y = 0;
             msg_drone_pos_vision.pose.orientation.w = -1000;
         }
         else{
               //发布相对相机的物体实际位置
               target_position_of_img.x() = msg_target_pose_from_img.pose.position.x;
               target_position_of_img.y() = msg_target_pose_from_img.pose.position.y;
               target_position_of_img.z() = msg_target_pose_from_img.pose.position.z;
               //发布相机的物体实际位置^^^

               //坐标转换，乘TF矩阵得到物体相对飞机的实际坐标点target_position_of_drone
               target_position_of_drone = tf_camera_to_drone * (tf_image_to_enu * target_position_of_img);
            //    cout << "target_position_of_drone-x = " << target_position_of_drone.x() << endl;
                // cout << "target_position_of_drone-y = " << target_position_of_drone.y() << endl;
            //    cout << "target_position_of_drone-z = " << target_position_of_drone.z() << endl;

               //坐标转换，乘TF矩阵得到物体相对飞机的实际坐标点target_position_of_drone ^^^

               //计算该物体该时刻的飞机姿态
               geometry_msgs::PoseStamped synchronized_att;
               while(1){
                   if(pose_queue.empty()){ //如果为空
                       break;
                   }
                   else{ //不为空
                       synchronized_att = pose_queue.front();
                       double temp = double(synchronized_att.header.stamp.toSec());
                      // printf("tenp is %.6f\n",temp);
                      // printf("pic is %.6f\n",image_ros_time);
                       if(image_ros_time >= temp){
                           break;
                       }else{
                           pose_queue.pop();
                       }
                   }
               }
               //计算该物体该时刻的飞机姿态^^^

               //飞机姿态转换为euler角
               drone_euler = quaternion2euler(synchronized_att.pose.orientation.x,synchronized_att.pose.orientation.y,synchronized_att.pose.orientation.z,synchronized_att.pose.orientation.w);
               //飞机姿态转换为euler角^^^

               //减去初始euler角
            //    cout << "euler-z real-time = " << drone_euler.z << endl;
            //    cout << "init ------z =" << drone_euler_init.z << endl;
               drone_euler.z  = drone_euler.z - drone_euler_init.z;
               
            //    cout << "euler-z final = " << drone_euler.z << endl;
               //减去初始euler角^^^

               //减去初始后转换为四元数
               drone_quaternion = euler2quaternion_eigen(drone_euler.x,drone_euler.y,drone_euler.z);
               //减去初始后转换为四元数^^^

               //去除飞机姿态对距离预测影响
               tf_drone_to_world = Eigen::Isometry3d::Identity();
               tf_drone_to_world.prerotate(drone_quaternion.toRotationMatrix());
               tf_drone_to_world.pretranslate(Eigen::Vector3d(0,0,0));
               //去除飞机姿态对距离预测影响^^^

               //计算不受影响的距离
               target_position_of_world = tf_drone_to_world * target_position_of_drone;
            //    cout <<  target_position_of_drone.x();

               drone_pos_vision.x() = target_position_of_world.x();
               drone_pos_vision.y() = target_position_of_world.y();
               drone_pos_vision.z() = target_position_of_world.z();
               //计算不受影响的距离^^^
               
               //
/*
               if((drone_pos_vision.x()>=2||drone_pos_vision.x()<=0)||(drone_pos_vision.y()>=0.6||drone_pos_vision.y()<=-0.6)||(drone_pos_vision.z()>=0.6||drone_pos_vision.z()<=-0.6)){
	           msg_drone_pos_vision.pose.orientation.w = -1000;}
               else{
		   msg_drone_pos_vision.pose.orientation.w = 1;}
*/
               //加上对应local_position
               //drone_pos_vision.x() = drone_pos_vision.x() + synchronized_att.pose.position.x;
               //drone_pos_vision.x() = drone_pos_vision.y() + synchronized_att.pose.position.y;
               //drone_pos_vision.z() = drone_pos_vision.z() + synchronized_att.pose.position.z;


               msg_drone_pos_vision.header.stamp = ros::Time::now();
               msg_drone_pos_vision.pose.position.x = drone_pos_vision.x();
               msg_drone_pos_vision.pose.position.y = drone_pos_vision.y();
               msg_drone_pos_vision.pose.position.z = drone_pos_vision.z();

               msg_drone_pos_vision.pose.orientation.x = id_name;
               msg_drone_pos_vision.pose.orientation.w = 1;

                // target_pose_world
               msg_target_pose_world.header.stamp = ros::Time::now();
               msg_target_pose_world.pose.position.x = msg_drone_pos_vision.pose.position.x + vision_pose_msg.pose.position.x;
               msg_target_pose_world.pose.position.y = msg_drone_pos_vision.pose.position.y + vision_pose_msg.pose.position.y;
               msg_target_pose_world.pose.position.z = msg_drone_pos_vision.pose.position.z + vision_pose_msg.pose.position.z;


               
            //    cout<<"x is :"<<msg_drone_pos_vision.pose.position.x<<"    "<<"y is :"<<msg_drone_pos_vision.pose.position.y<<"     "<<"z is :"<<msg_drone_pos_vision.pose.position.z<<endl;
            //    cout<<"id is :"<<msg_drone_pos_vision.pose.orientation.x<<endl;
            //    cout<<"标志位是:"<<msg_drone_pos_vision.pose.orientation.w<<endl;
         }

        if(msg_drone_pos_vision.pose.position.y>=0.6||msg_drone_pos_vision.pose.position.y<=-0.6||msg_drone_pos_vision.pose.position.z>=0.6||msg_drone_pos_vision.pose.position.z<=-0.6){
               msg_drone_pos_vision.pose.orientation.w = -1000;
        }
        msg_target_pose_from_img_pub.publish(msg_target_pose_from_img);
    // cout<<"x is :"<<msg_drone_pos_vision.pose.position.x<<"    "<<"y is :"<<msg_drone_pos_vision.pose.position.y<<"     "<<"z is :"<<msg_drone_pos_vision.pose.position.z<<endl;
    // cout<<"id is :"<<msg_drone_pos_vision.pose.orientation.x<<endl;
    // cout<<"标志位是:"<<msg_drone_pos_vision.pose.orientation.w<<endl;
	drone_pos_vision_pub.publish(msg_drone_pos_vision);     
    target_pose_world_pub.publish(msg_target_pose_world);   
        rate.sleep();
    }
    return 0;
}

void plane_attitude_sub(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    plane_atti_msg = *msg;
    // cout << "msg->pose.orientation.z: " << msg->pose.orientation.z << endl;
    drone_euler_real = quaternion2euler(plane_atti_msg.pose.orientation.x,plane_atti_msg.pose.orientation.y,plane_atti_msg.pose.orientation.z,plane_atti_msg.pose.orientation.w);
    // cout  <<  "drone_euler_real z  =" << drone_euler_real.z << endl; 
    pose_queue.push(*msg);
}

void vision_pose_sub(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    vision_pose_msg = *msg;
}


void target_corner_sub(const geometry_msgs::PoseStamped::ConstPtr& msg){

    targetDetectFlag = false;
    if(msg->pose.orientation.x < 0) //没有识别到目标
    {

         targetDetectFlag = false;
    }
    else{
        //记录图像获取时间
        image_ros_time = double(msg->pose.position.x);
        //记录id
        id_name = int(msg->pose.position.z)+1;
        //目标框的宽度 xmax - xmin
        target_width = int(msg->pose.orientation.z - msg->pose.orientation.x);
        //目标框的高度 ymax - ymin
        target_height = int(msg->pose.orientation.w - msg->pose.orientation.y);
        //目标框左上角的点
        target_left_up.x = int(max(0,int(msg->pose.orientation.x)));  //xmin
        target_left_up.y = int(max(0,int(msg->pose.orientation.y)));  //ymin
        //目标框右下角的点
        target_right_down.x = int(min(640,int(msg->pose.orientation.z)));  //xmax
        target_right_down.y = int(min(640,int(msg->pose.orientation.w)));  //ymax
        //目标框的中心点位置
        yolo_center.x = (target_left_up.x + target_right_down.x)/2.0;
        yolo_center.y = (target_left_up.y + target_right_down.y)/2.0;
        //根据小孔成像原理估计深度
        msg_target_pose_from_img.header.stamp = ros::Time::now();
        msg_target_pose_from_img.pose.orientation.x = 1;
        msg_target_pose_from_img.pose.position.z = scale_size * target_width_world * fx_color / target_width;
        msg_target_pose_from_img.pose.position.x = msg_target_pose_from_img.pose.position.z * (yolo_center.x-cx_color) / fx_color;
        msg_target_pose_from_img.pose.position.y = msg_target_pose_from_img.pose.position.z * (yolo_center.y-cy_color) / fy_color;

        targetDetectFlag = true;
    }
}

void tf_param_set() {
    //image coordinate to ENU coordinate

    tf_image_to_enu = Eigen::Isometry3d::Identity();
    tf_image_to_enu.matrix() << 0, 0, 1, 0,
            -1, 0, 0, 0,
            0, -1, 0, 0,
            0, 0, 0, 1;

    //the camera position of drone, now only translate , not rotation yet
    // tf is based on ENU axis
    // tf_camera_drone[0] = 0.06;
    // tf_camera_drone[1] = -0.05;
    // tf_camera_drone[2] = 0.1;
    tf_camera_drone[0] = 0.0;
    tf_camera_drone[1] = 0.0;
    tf_camera_drone[2] = 0.0;

    Eigen::Vector3d pose_camera_of_drone;
    pose_camera_of_drone.x() = tf_camera_drone[0];
    pose_camera_of_drone.y() = tf_camera_drone[1];
    pose_camera_of_drone.z() = tf_camera_drone[2];



    tf_camera_to_drone = Eigen::Isometry3d::Identity();
    tf_camera_to_drone.matrix() << 1, 0, 0, pose_camera_of_drone.x(),
            0, 1, 0, pose_camera_of_drone.y(),
            0, 0, 1, pose_camera_of_drone.z(),
            0 ,0, 0, 1;
}

void get_init_yaw() {
    //获取初始飞机姿态
    drone_euler_init = quaternion2euler(plane_atti_msg.pose.orientation.x,plane_atti_msg.pose.orientation.y,plane_atti_msg.pose.orientation.z,plane_atti_msg.pose.orientation.w);
    if(abs(drone_euler_init.z) > 0.000001)
        got_attitude_init = true;
}

/**
 * 将欧拉角转化为四元数
 * @param roll
 * @param pitch
 * @param yaw
 * @return 返回四元数
 */
geometry_msgs::Quaternion euler2quaternion(float roll, float pitch, float yaw){
    geometry_msgs::Quaternion temp;
    temp.w = cos(roll/2)*cos(pitch/2)*cos(yaw/2) + sin(roll/2)*sin(pitch/2)*sin(yaw/2);
    temp.x = sin(roll/2)*cos(pitch/2)*cos(yaw/2) - cos(roll/2)*sin(pitch/2)*sin(yaw/2);
    temp.y = cos(roll/2)*sin(pitch/2)*cos(yaw/2) + sin(roll/2)*cos(pitch/2)*sin(yaw/2);
    temp.z = cos(roll/2)*cos(pitch/2)*sin(yaw/2) - sin(roll/2)*sin(pitch/2)*cos(yaw/2);
    return temp;
}

Eigen::Quaterniond euler2quaternion_eigen(float roll, float pitch, float yaw){
    Eigen::Quaterniond temp;
    temp.w() = cos(roll/2)*cos(pitch/2)*cos(yaw/2) + sin(roll/2)*sin(pitch/2)*sin(yaw/2);
    temp.x() = sin(roll/2)*cos(pitch/2)*cos(yaw/2) - cos(roll/2)*sin(pitch/2)*sin(yaw/2);
    temp.y() = cos(roll/2)*sin(pitch/2)*cos(yaw/2) + sin(roll/2)*cos(pitch/2)*sin(yaw/2);
    temp.z() = cos(roll/2)*cos(pitch/2)*sin(yaw/2) - sin(roll/2)*sin(pitch/2)*cos(yaw/2);
    return temp;
}

/**
 * 将四元数转化为欧拉角形式
 * @param x
 * @param y
 * @param z
 * @param w
 * @return 返回Vector3的欧拉角
 */
geometry_msgs::Vector3 quaternion2euler(float x, float y, float z, float w){
    geometry_msgs::Vector3 temp;
    temp.x = atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (x * x + y * y));
    // I use ENU coordinate system , so I plus ' - '
    temp.y = asin(2.0 * (- z * x + w * y));
    temp.z = atan2(2.0 * (w * z + x * y), 1.0 - 2.0 * (y * y + z * z));
    return temp;
}
