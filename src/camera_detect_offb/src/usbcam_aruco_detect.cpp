//
// Created by zph on 2021/1/5.
//
// improved code to replace the former one by sdx
// input: usb cam video frame
// output: aruco pose in uav frame
// purpose: detect aruco pose using cam on uav

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <ros/ros.h>
#include <csignal>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <string>
#include<Eigen/Core>
#include<Eigen/Geometry>
using namespace cv;
using namespace std;
// #global param
int swarm_ID = 0;
std::string uav_name = "/uav"+to_string(swarm_ID);
bool DisplayPic = true;
int ros_seq_count = 0;
struct UAV_POS
{
    float x;
    float y;
    float z;
};
struct SWARM_POS
{
    UAV_POS poses[4];
    UAV_POS vel;
};
// ## usbcam param
cv::VideoCapture inputVideo;
float pub_rate = 30;//unit: Hz
int usbcam_index = 0;
cv::Mat cameraMatrix = (Mat_<float>(3, 3) << 547.2809749275908, 0.0, 285.5785999106521,
                                                        0.0, 547.2593192688294, 241.7048458185163,
                                                        0.0, 0.0, 1.0);//预先初始化，之后从文件载入
cv::Mat distCoeffs = (Mat_<float>(1, 5) << -0.36880523799774273, 0.1602523610541351,
                                                        -0.0003667070515998557, -0.0003697550896808344,
                                                        0.0);//摄像机的5个畸变系数：k1,k2,p1,p2,k3
cv::Mat imageCopy;
cv::Mat image;
// ## aruco param
ros::Publisher aruco_num_pub;
ros::Publisher uwb_pub;
int aruco_id_bound_upper = 10;
int aruco_id_bound_lower = 0;
float aruco_size = 0.048;//unit:m
int aruco_dic_index = 4;
Ptr<aruco::Dictionary> dictionary;
// coordinate transform param
geometry_msgs::PoseStamped uav_cur_pose;
nav_msgs::Odometry uav_cur_odom;
float uav_init_x = 0;
float uav_init_y = 0;
double ft_servo_angle = 0;

// tool func
template<typename T>
void readParam(ros::NodeHandle &nh, std::string param_name, T& loaded_param) {
    // template to read param from roslaunch
    const string& node_name = ros::this_node::getName();
    param_name = node_name + "/" + param_name;
    if (!nh.getParam(param_name, loaded_param)) {
        ROS_ERROR_STREAM("Failed to load " << param_name << ", use default value");
        //TODO:print default value
    }
    else{
        ROS_INFO_STREAM("Load " << param_name << " success");
        //TODO:print loaded value

    }
}

void loadRosParams(ros::NodeHandle &nh) {
    readParam<int>(nh, "swarm_ID",swarm_ID);
    readParam<int>(nh, "aruco_dic_index",aruco_dic_index);
    readParam<int>(nh, "usbcam_index",usbcam_index);
    readParam<int>(nh, "aruco_id_bound_upper",aruco_id_bound_upper);
    readParam<int>(nh, "aruco_id_bound_lower",aruco_id_bound_lower);
    readParam<bool>(nh, "DisplayPic",DisplayPic);
    readParam<float>(nh,"aruco_size",aruco_size);
    readParam<float>(nh,"pub_rate",pub_rate);
    readParam<float>(nh,"uav_init_x",uav_init_x);
    readParam<float>(nh,"uav_init_y",uav_init_y);
    uav_name = "/uav"+to_string(swarm_ID);
    uav_cur_pose.pose.orientation.w = 1;
    uav_cur_pose.pose.position.x = uav_init_x;
    uav_cur_pose.pose.position.y = uav_init_y;
    //print params
    ROS_INFO_STREAM("swarm_ID = "<<swarm_ID);
    ROS_INFO_STREAM("aruco_dic_index = "<<aruco_dic_index);
    ROS_INFO_STREAM("usbcam_index = "<<usbcam_index);
    ROS_INFO_STREAM("DisplayPic = "<<DisplayPic);
    ROS_INFO_STREAM("aruco_size = "<<aruco_size);
    ROS_INFO_STREAM("aruco_id_bound_upper = "<<aruco_id_bound_upper);
    ROS_INFO_STREAM("aruco_id_bound_lower = "<<aruco_id_bound_lower);
    ROS_INFO_STREAM("pub_rate = "<<pub_rate);
    ROS_INFO_STREAM("uav_init_pos = "<<uav_init_x<<","<<uav_init_y);
    //set aruco dic
    switch (aruco_dic_index) {
        case 4:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
            break;
        case 5:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_50);
            break;
        case 6:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
            break;
        default:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
            break;
    }
}

void loadCameraParams(ros::NodeHandle &nh) {
    //read cam param from roslaunch
    vector<float> rosParamsCameraMatrix(9);
    vector<float> rosParamsDistCoeffs(5);
    readParam<vector<float>>(nh, "cameraMatrix", rosParamsCameraMatrix);
    readParam<vector<float>>(nh, "cameraDistCoeffs", rosParamsDistCoeffs);
    // give to global variable
    for (int j = 0; j < 9; ++j) {
        cameraMatrix.at<float>(j) = rosParamsCameraMatrix[j];
    }
    ROS_INFO_STREAM("cameraMatrix:\n" << cameraMatrix);
    for (int k = 0; k < 5; ++k) {
        distCoeffs.at<float>(k) = rosParamsDistCoeffs[k];
    }
    ROS_INFO_STREAM("distCoeffs:\n" << distCoeffs);
}

void uwb_send(SWARM_POS swarm_info){
    // put current uav self velocity
    swarm_info.vel.x = uav_cur_odom.twist.twist.linear.x;
    swarm_info.vel.y = uav_cur_odom.twist.twist.linear.y;
    swarm_info.vel.z = uav_cur_odom.twist.twist.linear.z;
    //

    //self pos
    swarm_info.poses[swarm_ID-1].x = uav_cur_pose.pose.position.x;
    swarm_info.poses[swarm_ID-1].y = uav_cur_pose.pose.position.y;
    swarm_info.poses[swarm_ID-1].z = uav_cur_pose.pose.position.z;
    //send
    std::string s(sizeof(SWARM_POS), 0);
    memcpy((void*)(s.c_str()), (void*)(&swarm_info), sizeof(SWARM_POS));
    std_msgs::String uwb_data;
    uwb_data.data = s;
    uwb_pub.publish(uwb_data);
}

void detect_aruco(SWARM_POS & swarm_info){
    // init swarm info
    UAV_POS zero_pos;
    zero_pos.x = 0;
    zero_pos.y = 0;
    zero_pos.z = 0;
    for(int i=0;i<4;i++) swarm_info.poses[i]=zero_pos;//init
    swarm_info.vel = zero_pos;
    //detect aruco
    double current_servo_angle = ft_servo_angle;
    inputVideo >> image;
    image.copyTo(imageCopy);
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners;
    vector<Vec3d> rvecs, tvecs;
    cv::aruco::detectMarkers(image, dictionary, corners, ids);
    // unique detect result
    std::vector<int> unique_ids;
    std::vector<std::vector<cv::Point2f> > unique_corners;
    int id_find[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while(!ids.empty()){
        if(ids.back()<aruco_id_bound_lower || ids.back()>aruco_id_bound_upper) {
            ids.pop_back();
            corners.pop_back();
            continue;//not id we need, pass
        }
        else{
            //id we want, check repeat
            if(id_find[ids.back()]==0){
                // unique id, add
                id_find[ids.back()]=1;
                unique_ids.push_back(ids.back());
                unique_corners.push_back(corners.back());
                ids.pop_back();
                corners.pop_back();
            }
            else{
                //not unique, pass
                ids.pop_back();
                corners.pop_back();
            }
        }
        }
    //let ids and corners to be unique, avoid code conflict below
    while(!unique_ids.empty()){
        ids.push_back(unique_ids.back());
        corners.push_back(unique_corners.back());
        unique_ids.pop_back();
        unique_corners.pop_back();
    }

    // estimate pose
    if (!ids.empty()) {
        // publish detected markers number
        std_msgs::Int32 aruco_num;
        aruco_num.data = ids.size();
        aruco_num_pub.publish(aruco_num);
        //pose estimate
        cv::aruco::estimatePoseSingleMarkers(corners, aruco_size, cameraMatrix, distCoeffs, rvecs, tvecs);
        // marker detected
        for(int i = 0;i<ids.size();i++){

            ROS_INFO_STREAM_THROTTLE(1,"aruco detected, id :"<<ids[i]);
            // coordinate transform: aruco frame to camera frame
            cv::Affine3d axis_to_cam=cv::Affine3d(rvecs[i],tvecs[i]);
            cv::Affine3d cam_to_axis = axis_to_cam;
            cv::Matx44d world_to_cam_mat;
            world_to_cam_mat << 0,0,1,0,-1,0,0,0,0,-1,0,0,0,0,0,1;
            cv::Affine3d world_to_cam(world_to_cam_mat);
            cv::Affine3d world_to_axis = cam_to_axis.concatenate(world_to_cam);

            tf::Quaternion q;
            double theta = sqrt(world_to_axis.rvec()[0] * world_to_axis.rvec()[0]
                                 + world_to_axis.rvec()[1] * world_to_axis.rvec()[1]
                                 + world_to_axis.rvec()[2] * world_to_axis.rvec()[2]);
            tf::Vector3 axis = tf::Vector3(world_to_axis.rvec()[0]/theta,
                                           world_to_axis.rvec()[1]/theta,
                                           world_to_axis.rvec()[2]/theta);
            q.setRotation(axis,theta);
            //camera frame to uav frame
            Eigen::Vector3d aruco_pos(world_to_axis.translation()[0],
                                      world_to_axis.translation()[1],
                                      world_to_axis.translation()[2]);
            Eigen::AngleAxisd ft_servo_rotation(-current_servo_angle, Eigen::Vector3d(0,0,1));
            Eigen::Quaterniond q_ft_servo(ft_servo_rotation);
            //for debug
            //Eigen::Vector3d euler = q_ft_motor.toRotationMatrix().eulerAngles(0, 1, 2);
            // end of debug
            Eigen::Quaterniond q_uav(uav_cur_pose.pose.orientation.w,
                                     uav_cur_pose.pose.orientation.x,
                                     uav_cur_pose.pose.orientation.y,
                                     uav_cur_pose.pose.orientation.z);
            Eigen::Isometry3d T(q_ft_servo*q_uav);
            aruco_pos = T*aruco_pos;//uav frame
            //put detected result to swarm info
            double fix_err=1.25;
            swarm_info.poses[ids[i]-1].x = aruco_pos.x()*1.25;
            swarm_info.poses[ids[i]-1].y = aruco_pos.y()*1.25;
            swarm_info.poses[ids[i]-1].z = aruco_pos.z()*1.25;



//            //make marker
//            visualization_msgs::Marker one_marker;// record and show pose
//            one_marker.header.frame_id = "world";
//            one_marker.header.stamp = ros::Time::now();
////            one_marker.header.seq = ids[i];
//            one_marker.header.seq = ros_seq_count;
//            ros_seq_count++;
//            one_marker.id = ids[i];
//            one_marker.ns = uav_name;
//            one_marker.type = visualization_msgs::Marker::SPHERE;
//            one_marker.action = visualization_msgs::Marker::ADD;
//            one_marker.lifetime = ros::Duration(0.1);
//            one_marker.color.g = 1;
//            one_marker.color.a = 0.5;
//            one_marker.scale.x = 0.1;
//            one_marker.scale.y = 0.1;
//            one_marker.scale.z = 0.1;
//            one_marker.pose.position.x = aruco_pos.x()+uav_cur_pose.pose.position.x;
//            one_marker.pose.position.y = aruco_pos.y()+uav_cur_pose.pose.position.y;
//            one_marker.pose.position.z = aruco_pos.z()+uav_cur_pose.pose.position.z;
//            one_marker.pose.orientation.x = q.x();
//            one_marker.pose.orientation.y = q.y();
//            one_marker.pose.orientation.z = q.z();
//            one_marker.pose.orientation.w = q.w();
//            aruco_markers.markers.push_back(one_marker);
//            // for view marker id
//            visualization_msgs::Marker text_marker;// record and show pose
//            text_marker.header.frame_id = "world";
//            text_marker.header.stamp = ros::Time::now();
////            text_marker.header.seq = 1000+ids[i];//avoid id conflict
//            text_marker.header.seq = ros_seq_count;
//            ros_seq_count++;
//            text_marker.id = 1000+ids[i];//+1000, avoid id conflict
//            text_marker.ns = uav_name;
//            text_marker.text = to_string(ids[i]);
//            text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
//            text_marker.action = visualization_msgs::Marker::ADD;
//            text_marker.lifetime = ros::Duration(0.1);
//            text_marker.color.r = 1;
//            text_marker.color.a = 1;
//            text_marker.scale.z = 0.15;
//            text_marker.pose.position.x = aruco_pos.x()+uav_cur_pose.pose.position.x;
//            text_marker.pose.position.y = aruco_pos.y()+uav_cur_pose.pose.position.y;
//            text_marker.pose.position.z = aruco_pos.z()+uav_cur_pose.pose.position.z+0.1;//a little bit above marker
//            aruco_markers.markers.push_back(text_marker);
        }

        if(DisplayPic){
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
        }
    }
    if(DisplayPic){
        cv::imshow("aruco_detect_result", imageCopy);
    }

}

void ft_servo_angle_cb(const geometry_msgs::Point32& msg){
    ft_servo_angle = msg.x;
}

void uav_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    uav_cur_pose = *msg;
    uav_cur_pose.pose.position.x += uav_init_x;
    uav_cur_pose.pose.position.y += uav_init_y;
}

void uav_odom_cb(const nav_msgs::Odometry::ConstPtr& msg){
    uav_cur_odom = *msg;
}

//
int main(int argc, char **argv) {
    // ros node init
    ros::init(argc, argv, "usbcam_aruco_detect",ros::init_options::AnonymousName);
    ros::NodeHandle nh;
//    ros::NodeHandle nh(("uav"+to_string(swarm_ID)));
    // load param
    loadCameraParams(nh);
    loadRosParams(nh);
    // ros topic pub and sub
    uwb_pub = nh.advertise<std_msgs::String>(uav_name+"/nlink_linktrack_data_transmission", 1);
    aruco_num_pub = nh.advertise<std_msgs::Int32>(uav_name+"/detected_aruco_num", 1);
    ros::Subscriber ftmotor_angle_sub = nh.subscribe(uav_name+"/ft_servo_angle", 1,ft_servo_angle_cb);
    ros::Subscriber uav_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>(uav_name+"/mavros/local_position/pose", 2, uav_pose_cb);
    ros::Subscriber uav_odom_sub = nh.subscribe<nav_msgs::Odometry>(uav_name+"/mavros/local_position/odom", 2, uav_odom_cb);

    //open usbcam
    inputVideo = cv::VideoCapture(usbcam_index);
    inputVideo.open(usbcam_index);
    inputVideo.set(3, 800);
    inputVideo.set(4,600);

    //start detect
    ros::Rate ros_loop(pub_rate);
    while(ros::ok()){
        visualization_msgs::MarkerArray  aruco_markers;
        SWARM_POS swarm_info;
        if(inputVideo.isOpened()){
            if (waitKey(5) == 27) break;
            auto last_tick = (double) getTickCount();
            detect_aruco(swarm_info);
            double time_cost = ((double) getTickCount() - last_tick) / getTickFrequency();
            ROS_INFO_STREAM_THROTTLE(2, "Detect Time Cost = " << time_cost * 1000 << " ms");
        }
        else{
            ROS_ERROR_STREAM_THROTTLE(1,"Cannot Open Camera!");
        }
        // publish aruco pose info to uwb string type
        uwb_send(swarm_info);
        //ros loop
        ros::spinOnce();
        ros_loop.sleep();

    }
    inputVideo.release();

}

