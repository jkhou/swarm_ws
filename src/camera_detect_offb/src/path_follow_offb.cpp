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
#include <ros/package.h>
using namespace std;

// global variable
mavros_msgs::State uav_cur_state;
geometry_msgs::PoseStamped uav_cur_pose;
geometry_msgs::PoseStamped target_cur_pose;

float uav_init_x = 0;
float uav_init_y = 0;

int swarm_ID = 2;
std::string uav_name = "/uav"+to_string(swarm_ID);
int ctrl_rate = 30;
int aruco_num = 0;
string traj_csv_name = "/cfg/path_circle.csv";
bool repeat_path = false;

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

std::vector<std::vector<double>> read_csv_traj(const std::string &file)
{
    std::vector<std::vector<double>> csv_traj;

    FILE *fp;
    fp=fopen(file.c_str(),"r");
    if(!fp)
    {
        ROS_ERROR_STREAM("cannot open file: " + file);
    }
    while(1){
        std::vector<double> traj_point(3);
        fscanf(fp,"%lf,%lf,%lf",&traj_point[0],&traj_point[1],&traj_point[2]);
        csv_traj.push_back(traj_point);
        if(feof(fp)) break;
    }
    fclose(fp);
    return csv_traj;
}

void loadRosParams(ros::NodeHandle &nh) {
    readParam<int>(nh, "swarm_ID", swarm_ID);
    readParam<int>(nh, "ctrl_rate", ctrl_rate);
    readParam<string>(nh, "traj_csv_name",traj_csv_name);
    readParam<bool>(nh, "repeat_path",repeat_path);
//    readParam<float>(nh,"uav_init_x",uav_init_x);
//    readParam<float>(nh,"uav_init_y",uav_init_y);
    uav_name = "/uav" + to_string(swarm_ID);
    uav_cur_pose.pose.orientation.w = 1;
//    uav_cur_pose.pose.position.x = uav_init_x;
//    uav_cur_pose.pose.position.y = uav_init_y;
    //print params
    ROS_INFO_STREAM("swarm_ID = " << swarm_ID);
    ROS_INFO_STREAM("ctrl_rate = " << ctrl_rate);
    ROS_INFO_STREAM("traj_name = " << traj_csv_name);
//    ROS_INFO_STREAM("uav_init_pos = "<<uav_init_x<<","<<uav_init_y);
}

// CB function
void uav_state_cb(const mavros_msgs::State::ConstPtr& msg){
    uav_cur_state = *msg;
}

void uav_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    uav_cur_pose = *msg;
}



int main (int argc, char** argv) {
    // ros init
    ros::init(argc, argv, "consensus_offb", ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    // load param
    loadRosParams(nh);
    std::string pkg_path = ros::package::getPath("camera_detect");
    std::vector<std::vector<double>> csv_traj = read_csv_traj(pkg_path + traj_csv_name);
    //ros pub and sub
    ros::Subscriber uav_state_sub = nh.subscribe<mavros_msgs::State>
            (uav_name+"/mavros/state", 10, uav_state_cb);
    ros::Subscriber uav_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>
            (uav_name+"/mavros/local_position/pose", 2, uav_pose_cb);
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
    int traj_index = 0;

    //main ctrl loop
    while(ros::ok()) {
        if (uav_cur_state.armed) {
            if (uav_cur_state.mode == "OFFBOARD") {
                double off_board_start = ros::Time::now().toSec();
                off_board_start += 20.0;
                if(!takeoff){
                    //take off to some height
                    geometry_msgs::PoseStamped takeoff_pose;
                    takeoff_pose.pose.position.x = uav_cur_pose.pose.position.x;
                    takeoff_pose.pose.position.y = uav_cur_pose.pose.position.y;
                    takeoff_pose.pose.position.z = 1;
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
                    for(int i = 10000; ros::ok() && i > 0; --i){
                        offb_setpoint_pub.publish(pose_before_offb);
                        double off_board_exce = ros::Time::now().toSec();
                        if(off_board_exce >= off_board_start)
                            break;
                        ros::spinOnce();
                        ctrl_loop.sleep();
                    }
                    just_offb = false;
                    pose_offb_hover = pose_before_offb;
                }
                // has take off, into offboard control
                ROS_INFO_STREAM_THROTTLE(1, uav_name+" in Offboard cmd");
                if(traj_index+1 < csv_traj.size()){
                    geometry_msgs::PoseStamped traj_pose;
                    traj_pose.pose.position.x = pose_before_offb.pose.position.x;
                    traj_pose.pose.position.y = csv_traj[traj_index][0]  + pose_before_offb.pose.position.y;
                    traj_pose.pose.position.z = - csv_traj[traj_index][1] + pose_before_offb.pose.position.z;
                    // traj_pose.pose.position.z = 1;
                    traj_pose.header.frame_id = uav_name;
                    traj_pose.header.stamp = ros::Time::now();
                    offb_setpoint_pub.publish(traj_pose);
                    pose_offb_hover = uav_cur_pose;
                    traj_index++;
                }
                else{
                    if(repeat_path){
                        traj_index=0;//从头开始
                    }
                    else{
                        //悬停
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