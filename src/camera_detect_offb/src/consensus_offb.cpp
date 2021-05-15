//
// Created by zph on 2021/1/12.
// px4 offboard node for testing consensus

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/TwistStamped.h>
#include <string>
using namespace std;

// global variable

mavros_msgs::State uav_cur_state;
geometry_msgs::PoseStamped uav_cur_pose;
float uav_init_x = 0;
float uav_init_y = 0;

int swarm_ID = 0;
std::string uav_name = "/uav"+to_string(swarm_ID);
int ctrl_rate = 30;
int aruco_num = 0;


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
    readParam<int>(nh, "swarm_ID", swarm_ID);
    readParam<int>(nh, "ctrl_rate", ctrl_rate);
    readParam<float>(nh,"uav_init_x",uav_init_x);
    readParam<float>(nh,"uav_init_y",uav_init_y);
    uav_name = "/uav" + to_string(swarm_ID);
    uav_cur_pose.pose.orientation.w = 1;
    uav_cur_pose.pose.position.x = uav_init_x;
    uav_cur_pose.pose.position.y = uav_init_y;
    //print params
    ROS_INFO_STREAM("swarm_ID = " << swarm_ID);
    ROS_INFO_STREAM("ctrl_rate = " << ctrl_rate);
    ROS_INFO_STREAM("uav_init_pos = "<<uav_init_x<<","<<uav_init_y);
}

// CB function
void uav_state_cb(const mavros_msgs::State::ConstPtr& msg){
    uav_cur_state = *msg;
}

void uav_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    uav_cur_pose = *msg;
}

double sum_relative_x = 0;
double sum_relative_y = 0;
void aruco_pose_cb(const visualization_msgs::MarkerArray& msg) {
    //TODO: consider fusion of many poses to decide true relative
    aruco_num = msg.markers.size()/2.0;
    sum_relative_x = 0;
    sum_relative_y = 0;
    for(int i = 0; i<msg.markers.size();i++){
        sum_relative_x+=msg.markers[i].pose.position.x-uav_cur_pose.pose.position.x-uav_init_x;
        sum_relative_y+=msg.markers[i].pose.position.y-uav_cur_pose.pose.position.y-uav_init_y;
    }
    sum_relative_x = sum_relative_x/2.0;//one aruco correspond 2 marker, real dis should divide 2
    sum_relative_y = sum_relative_y/2.0;
    return;
}



int main (int argc, char** argv) {
    // ros init
    ros::init(argc, argv, "consensus_offb", ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    // load param
    loadRosParams(nh);
    //ros pub and sub
    ros::Subscriber uav_state_sub = nh.subscribe<mavros_msgs::State>
            (uav_name+"/mavros/state", 10, uav_state_cb);
    ros::Subscriber uav_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>
            (uav_name+"/mavros/local_position/pose", 2, uav_pose_cb);
    ros:: Subscriber aruco_pose_sub = nh.subscribe(uav_name+"/detected_aruco_pose",1, aruco_pose_cb);

    ros::Publisher offb_setpoint_pub = nh.advertise<geometry_msgs::PoseStamped>
            (uav_name+"/mavros/setpoint_position/local", 10);

    // ros::Publisher offb_setvel_pub = nh.advertise<geometry_msgs::TwistStamped>
    //         (uav_name+"/mavros/setpoint_attitude/cmd_vel", 10);

    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            (uav_name+"/mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            (uav_name+"/mavros/set_mode");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate ctrl_loop(ctrl_rate);
    // wait for FCU connection
    while(ros::ok() && !uav_cur_state.connected){
        ros::spinOnce();
        ctrl_loop.sleep();
    }
    // send a few setpoints before starting
    // Before entering Offboard mode,
    // you must have already started streaming setpoints.
    // Otherwise the mode switch will be rejected.
    geometry_msgs::PoseStamped pose_before_offb;
    for(int i = 10; ros::ok() && i > 0; --i){
        pose_before_offb = uav_cur_pose;
        offb_setpoint_pub.publish(pose_before_offb);
        ros::spinOnce();
        ctrl_loop.sleep();
    }

    bool takeoff = false;
    bool just_offb = true;//check whether plane change into offboard mode from other mode
    geometry_msgs::PoseStamped pose_offb_hover;//pose to hover in offboard mode
    pose_offb_hover = uav_cur_pose;

    //main ctrl loop
    while(ros::ok()) {
        if (uav_cur_state.armed) {
            if (uav_cur_state.mode == "OFFBOARD") {
                if(!takeoff){
                    //take off to some height
                    geometry_msgs::PoseStamped takeoff_pose;
                    takeoff_pose.pose.position.x = uav_cur_pose.pose.position.x;
                    takeoff_pose.pose.position.y = uav_cur_pose.pose.position.y;
                    takeoff_pose.pose.position.z = 0.5;
                    double err = 0.05;
                    while(fabs(takeoff_pose.pose.position.z-uav_cur_pose.pose.position.z)>err){
                        offb_setpoint_pub.publish(takeoff_pose);
                        ros::spinOnce();
                        ctrl_loop.sleep();
                    }
                    ROS_INFO_STREAM(uav_name+" take off done");
                    takeoff = true;
                    pose_before_offb = takeoff_pose;
                    pose_offb_hover = takeoff_pose;
                }
                if(just_offb){
                    //into offboard mode just now, stay still for a while, about several seconds
                    for(int i = 100; ros::ok() && i > 0; --i){
                        offb_setpoint_pub.publish(pose_before_offb);
                        ros::spinOnce();
                        ctrl_loop.sleep();
                    }
                    just_offb = false;
                    pose_offb_hover = pose_before_offb;
                }
                // has take off, into offboard control
                ROS_INFO_STREAM_THROTTLE(1, uav_name+" in Offboard cmd");
                if(aruco_num==0){
                    // no aruco, hold
                    ROS_INFO_STREAM_THROTTLE(1, uav_name+" not find aruco, hover");
                    offb_setpoint_pub.publish(pose_offb_hover);
                }
                else{
                    //find aruco, realize consensus
                    ROS_INFO_STREAM_THROTTLE(1, uav_name+" find "<<aruco_num<<" aruco");
                    double x_err = 0.2;
                    //method 1: vel ctrl
//                    if(fabs(sum_relative_x)>x_err){
//                        //move to lower err
//                        ROS_INFO_STREAM_THROTTLE(1, uav_name+" move to lower err");
//                        // give control value according to sum_relative_x
//                        double control_value = 0;
//                        if(fabs(sum_relative_x)>1.5) control_value=0.2*fabs(sum_relative_x)/sum_relative_x;
//                        else{
//                            control_value=sum_relative_x/10;
//                        }
//                        if(fabs(control_value)<0.05) control_value=0.05*fabs(control_value)/control_value;
//                        geometry_msgs::TwistStamped setvel;
//                        setvel.header.stamp = ros::Time::now();
//                        setvel.header.frame_id = uav_name;
//                        setvel.twist.linear.x = control_value;
//                        offb_setvel_pub.publish(setvel);
//                        //record pose
//                        pose_offb_hover = uav_cur_pose;
//                    }
//                    else{
//                        //dis err too small, no need to move
//                        ROS_INFO_STREAM_THROTTLE(1, uav_name+" dis err meet, hold");
//                        offb_setpoint_pub.publish(pose_offb_hover);
//                    }

                    //method 2: pos ctrl
                    if(fabs(sum_relative_x)>x_err){
                        //move to lower err
                        ROS_INFO_STREAM_THROTTLE(1, uav_name+" move to lower err");
                        // give control value according to sum_relative_x
                        double control_value = 0;
                        if(fabs(sum_relative_x)>1.5) control_value=0.2*fabs(sum_relative_x)/sum_relative_x;
                        else{
                            control_value=sum_relative_x/10;
                        }
                        if(fabs(control_value)<0.05) control_value=0.05*fabs(control_value)/control_value;
                        geometry_msgs::PoseStamped setpoint_pose;
                        setpoint_pose.pose.position.x = uav_cur_pose.pose.position.x+control_value;
                        setpoint_pose.pose.position.y = pose_before_offb.pose.position.y;
                        setpoint_pose.pose.position.z = 0.5;
                        offb_setpoint_pub.publish(setpoint_pose);
                        //record pose
                        pose_offb_hover = uav_cur_pose;
                    }
                    else{
                        //dis err too small, no need to move
                        ROS_INFO_STREAM_THROTTLE(1, uav_name+" dis err meet, hold");
                        offb_setpoint_pub.publish(pose_offb_hover);
                    }
                }


            }
            else{//not offb
                ROS_INFO_STREAM_THROTTLE(1, uav_name+" waiting for Offboard cmd");
                offb_setpoint_pub.publish(uav_cur_pose);
                pose_before_offb = uav_cur_pose;
                just_offb = true;
            }
        }
        else{//not arm
            ROS_INFO_STREAM_THROTTLE(1, uav_name+" waiting for Vehicle arm");
            offb_setpoint_pub.publish(uav_cur_pose);
            pose_before_offb = uav_cur_pose;
            takeoff=false;
            just_offb = true;
        }

        ros::spinOnce();
        ctrl_loop.sleep();
    }

    return 0;
}