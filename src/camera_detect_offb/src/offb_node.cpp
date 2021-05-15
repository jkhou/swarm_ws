/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <camera_detect/zzw.h>
#include <tf/transform_datatypes.h>
#include<Eigen/Core>
#include<Eigen/Geometry>
#include <geometry_msgs/Point32.h>


ros::Publisher aruco_vis_pub;
ros::Publisher ftmotor_ctl_pub;
// global variable
mavros_msgs::State uav_cur_state;
geometry_msgs::PoseStamped uav_cur_pos;
camera_detect::zzw small_aruco_pos;
double aruco_pos_x = 0, aruco_pos_y=0, aruco_pos_z=0;
bool aruco_isfind = false;
double ftmotor_start_pos = 0;
double ftmotor_cur_pos = 0;
double ftmotor_direction = M_PI/90;
// marker for aruco pos vis
visualization_msgs::Marker aruco_marker;

// CB function
void uav_state_cb(const mavros_msgs::State::ConstPtr& msg){
    uav_cur_state = *msg;
}

void uav_pos_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    uav_cur_pos = *msg;
}

void small_aruco_pos_cb(const camera_detect::zzw::ConstPtr& msg){
    small_aruco_pos = *msg;
    if (small_aruco_pos.id.empty()){
        ROS_INFO_THROTTLE(0.2, "no aruco marker is found!");
        aruco_pos_x=0;
        aruco_pos_y=0;
        aruco_pos_z=0;
        aruco_marker.pose.position.x = uav_cur_pos.pose.position.x+aruco_pos_x;
        aruco_marker.pose.position.y = uav_cur_pos.pose.position.y+aruco_pos_y;
        aruco_marker.pose.position.z = uav_cur_pos.pose.position.z+aruco_pos_z;
        aruco_vis_pub.publish(aruco_marker);
        
    }
    else{
        aruco_isfind = false;
        for(int i=0; i<small_aruco_pos.id.size();i++){
            if(small_aruco_pos.id.at(i)==0){
                double pos_x = small_aruco_pos.pose.at(i).position.x;
                double pos_y = small_aruco_pos.pose.at(i).position.y;
                double pos_z = small_aruco_pos.pose.at(i).position.z;
                double x = uav_cur_pos.pose.orientation.x;
                double y = uav_cur_pos.pose.orientation.y;
                double z = uav_cur_pos.pose.orientation.z;
                double w = uav_cur_pos.pose.orientation.w;
                Eigen::Vector3d aruco_pos(pos_x, pos_y, pos_z);
                Eigen::AngleAxisd ft_motor_rotation(-ftmotor_cur_pos, Eigen::Vector3d(0,0,1));
                Eigen::Quaterniond q_ft_motor(ft_motor_rotation);
                //for debug
                Eigen::Vector3d euler = q_ft_motor.toRotationMatrix().eulerAngles(0, 1, 2);
                std::cout << "Euler from quaternion in roll, pitch, yaw"<< std::endl << euler << std::endl;
//                ROS_INFO_THROTTLE(0.1, "euler angle:d%", euler[2]);
                // end of debug
                Eigen::Quaterniond qe(w,x,y,z);
                Eigen::Isometry3d Tw(q_ft_motor*qe);
                aruco_pos = Tw*aruco_pos;
                // aruco_pos = Tw.inverse()*aruco_pos;
                aruco_pos_x = aruco_pos.x();
                aruco_pos_y = aruco_pos.y();
                aruco_pos_z = aruco_pos.z();
                aruco_isfind = true;
                // tf::Quaternion q(x,y,z,w);
                // tf::Matrix3x3 m(q);
                // double roll, pitch, yaw;
                // m.getRPY(roll, pitch, yaw);
                // ROS_INFO_THROTTLE(0.1, "yaw = %f", yaw);
                //ROS_INFO_THROTTLE(0.2, "aruco_pos_x = %f, aruco_pos_y = %f, aruco_pos_z = %f", aruco_pos_x, aruco_pos_y, aruco_pos_z);
                aruco_marker.pose.position.x = uav_cur_pos.pose.position.x+aruco_pos_x;
                aruco_marker.pose.position.y = uav_cur_pos.pose.position.y+aruco_pos_y;
                aruco_marker.pose.position.z = uav_cur_pos.pose.position.z+aruco_pos_z;
                aruco_vis_pub.publish(aruco_marker);
                break;
            }
        }
        if(!aruco_isfind){
            aruco_pos_x=0;
            aruco_pos_y=0;
            aruco_pos_z=0;
            aruco_marker.pose.position.x = uav_cur_pos.pose.position.x+aruco_pos_x;
            aruco_marker.pose.position.y = uav_cur_pos.pose.position.y+aruco_pos_y;
            aruco_marker.pose.position.z = uav_cur_pos.pose.position.z+aruco_pos_z;
            aruco_vis_pub.publish(aruco_marker);
            ROS_INFO("no pos");

        }
        
    }
}

void ftmotor_ctl_cb(const ros::TimerEvent&){
    geometry_msgs::Point32  setpoint;
    if(ftmotor_cur_pos >= 2.618){
        ftmotor_direction = -ftmotor_direction;
    }
    if(ftmotor_cur_pos <= -2.618){
        ftmotor_direction = -ftmotor_direction;
    }
    ftmotor_cur_pos+= ftmotor_direction;
    setpoint.x = ftmotor_cur_pos;
    setpoint.y = 200;
    ftmotor_ctl_pub.publish(setpoint);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
    aruco_vis_pub = nh.advertise<visualization_msgs::Marker>( "aruco_pos_vis", 10 );
    ftmotor_ctl_pub = nh.advertise<geometry_msgs::Point32>( "/gimbal_commands", 10 );
    ros::Timer ftmotor_ctl_timer = nh.createTimer(ros::Duration(0.05), ftmotor_ctl_cb);
    ros::Subscriber uav_state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, uav_state_cb);
    ros::Subscriber uav_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>
            ("/mavros/local_position/pose", 2, uav_pos_cb);
    ros::Subscriber small_aruco_pos_sub = nh.subscribe<camera_detect::zzw>
            ("/aruco_detect/send_data_small", 2, small_aruco_pos_cb);
            
    ros::Publisher offb_setpos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);

    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && !uav_cur_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    aruco_marker.header.frame_id = "map";
    aruco_marker.header.stamp = ros::Time();
    aruco_marker.ns = "aruco";
    aruco_marker.id = 0;
    aruco_marker.type = visualization_msgs::Marker::SPHERE;
    aruco_marker.action = visualization_msgs::Marker::ADD;
    aruco_marker.pose.orientation.x = 0.0;
    aruco_marker.pose.orientation.y = 0.0;
    aruco_marker.pose.orientation.z = 0.0;
    aruco_marker.pose.orientation.w = 1.0;
    aruco_marker.scale.x = 0.3;
    aruco_marker.scale.y = 0.3;
    aruco_marker.scale.z = 0.3;
    aruco_marker.color.a = 1.0; // Don't forget to set the alpha!
    aruco_marker.color.r = 0.0;
    aruco_marker.color.g = 1.0;
    aruco_marker.color.b = 0.0;
    
    //send a few setpoints before starting
    // Before entering Offboard mode, 
    // you must have already started streaming setpoints. 
    // Otherwise the mode switch will be rejected. 
    geometry_msgs::PoseStamped pos_before_offb;
    for(int i = 10; ros::ok() && i > 0; --i){
        pos_before_offb = uav_cur_pos;
        offb_setpos_pub.publish(pos_before_offb);
        ros::spinOnce();
        rate.sleep();
    }


    while(ros::ok()){
        if(uav_cur_state.armed){
            if(uav_cur_state.mode == "OFFBOARD"){
                     
                if(aruco_isfind){
                    double dis_to_aruco = sqrt(aruco_pos_x*aruco_pos_x + aruco_pos_y*aruco_pos_y + aruco_pos_z*aruco_pos_z);
                    double safe_dis = 1.0;
                    if (dis_to_aruco>safe_dis){
                        geometry_msgs::PoseStamped pose;
                        pose.pose.position.x = uav_cur_pos.pose.position.x+aruco_pos_x*(dis_to_aruco-safe_dis)/dis_to_aruco;
                        pose.pose.position.y = uav_cur_pos.pose.position.y+aruco_pos_y*(dis_to_aruco-safe_dis)/dis_to_aruco;
                        pose.pose.position.z = uav_cur_pos.pose.position.z+aruco_pos_z*(dis_to_aruco-safe_dis)/dis_to_aruco;
                        // offb_setpos_pub.publish(pose);
                        offb_setpos_pub.publish(pose);
                        ROS_INFO_THROTTLE(1, "adjusting");
                        pos_before_offb = uav_cur_pos;    
                    }
                    else{
                        offb_setpos_pub.publish(pos_before_offb);
                        ROS_INFO_THROTTLE(2, "no need to adjust");

                    }
                }
                else{
                    offb_setpos_pub.publish(pos_before_offb);
                    ROS_INFO_THROTTLE(2, "specific aruco not find");
                }
                
             }
            else{
                ROS_INFO_THROTTLE(2, "waiting for Offboard cmd");
                offb_setpos_pub.publish(uav_cur_pos);
                pos_before_offb = uav_cur_pos;
            }
        }
        else{
            ROS_INFO_THROTTLE(2, "waiting for Vehicle arm");
            offb_setpos_pub.publish(uav_cur_pos);
            pos_before_offb = uav_cur_pos;

        }

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}