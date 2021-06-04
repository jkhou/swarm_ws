//
// Created by zph on 2021/1/28.
//
#include <iostream>
#include <ros/ros.h>
#include <csignal>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>
#include <string>
#include <nlink_parser/LinktrackNodeframe0.h>
#include <nlink_parser/LinktrackNodeframe3.h>
#include <geometry_msgs/Point.h>
#include <nlink_parser/SwarmInfoStamped.h>
#include <nlink_parser/UWBDisStamped.h>
using namespace std;
//global variable
int swarm_ID=0;
ros::Publisher aruco_pose_pub;
ros::Publisher uwb_dis_pub;
std::string local_detect_aruco;
double trans_scale = 500.0;//为了节省通信带宽，将double转int16数据传输，两者转换时乘的系数，依据是无人机大致活动范围，int16最大32767，32767/500约为6.4米，分辨率2mm
struct UAV_POS
{
    int16_t x;
    int16_t y;
    int16_t z;
};
struct SWARM_POS
{
    UAV_POS poses[4];
    UAV_POS vel;
};
int ros_seq_count = 0;
int uwb_seq_count = 0;

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

void uwb_recv_cb(const nlink_parser::LinktrackNodeframe0 &msg) {
    //发布为所有观察到的点的信息
    nlink_parser::SwarmInfoStamped swarm_info;
    //同时收到多个uwb的数据
    for(int j=0; j<msg.nodes.size(); j++){
        if(msg.nodes[j].id<1 || msg.nodes[j].id>4) continue;//表示并非飞机上的uwb
        //解析数据
        const std::vector<unsigned char>& s = msg.nodes[j].data;
        SWARM_POS rcv_info;
        memcpy((void*)(&rcv_info), (void*)(s.data()), sizeof(SWARM_POS));
        //将位置存入数组
        for(int i=0;i<4;i++) {
            UAV_POS one_uav_pos = rcv_info.poses[i];
            if (one_uav_pos.x==0 && one_uav_pos.y==0) continue;//表示当前没有看到这个点
            geometry_msgs::Point one_pos;
            one_pos.x = one_uav_pos.x/trans_scale;
            one_pos.y = one_uav_pos.y/trans_scale;
            one_pos.z = one_uav_pos.z/trans_scale;
//            if(int(msg.nodes[j].id)!=one_uav_pos.marker_id){
//                ROS_INFO_STREAM_THROTTLE(0.5, "1:uav"<< int(msg.nodes[j].id) <<" detect marker " << std::to_string(one_uav_pos.marker_id));
//            }
            swarm_info.poses[msg.nodes[j].id * 4 + i - 4] = one_pos;
        }
        //save a vel
        geometry_msgs::Point one_vel;
        one_vel.x = rcv_info.vel.x/trans_scale;
        one_vel.y = rcv_info.vel.y/trans_scale;
        one_vel.z = rcv_info.vel.z/trans_scale;
        swarm_info.vel[msg.nodes[j].id-1] = one_vel;
    }
    //加入自身检测到的数据
    SWARM_POS self_pos;
    memcpy((void*)(&self_pos), (void*)(local_detect_aruco.c_str()), sizeof(SWARM_POS));
    //将位置存入数组
    for(int i=0;i<4;i++) {
        UAV_POS one_uav_pos = self_pos.poses[i];
        if (one_uav_pos.x==0 && one_uav_pos.y==0) continue;//表示当前没有看到这个点
        geometry_msgs::Point one_pos;
        one_pos.x = one_uav_pos.x/trans_scale;
        one_pos.y = one_uav_pos.y/trans_scale;
        one_pos.z = one_uav_pos.z/trans_scale;
        //ROS_INFO_STREAM_THROTTLE(1, "2:uav"<< swarm_ID <<" detect marker " << std::to_string(one_uav_pos.marker_id));
        swarm_info.poses[swarm_ID * 4 + i - 4] = one_pos;
    }
    //自身速度
    geometry_msgs::Point one_vel;
    one_vel.x = self_pos.vel.x/trans_scale;
    one_vel.y = self_pos.vel.y/trans_scale;
    one_vel.z = self_pos.vel.z/trans_scale;
    swarm_info.vel[swarm_ID-1] = one_vel;
    //加入时间戳
    swarm_info.header.frame_id = "world";
    swarm_info.header.stamp = ros::Time::now();
    swarm_info.header.seq = ros_seq_count;
    ros_seq_count++;
    aruco_pose_pub.publish(swarm_info);

    return;
    
}

void uwb_loop_recv_cb(const std_msgs::StringConstPtr &msg) {
    //解析自己发送的数据
    local_detect_aruco = msg->data;
}

void uwb_dis_cb(const nlink_parser::LinktrackNodeframe3 &msg){
    nlink_parser::UWBDisStamped relative_dis;
    for(int i = 0; i<4; i++) relative_dis.distance[i]=-1;
    for(int i = 0; i<msg.nodes.size(); i++){
        if(msg.nodes[i].id<1 || msg.nodes[i].id>4) continue;
        relative_dis.distance[msg.nodes[i].id-1] = msg.nodes[i].dis;
    }
    relative_dis.header.frame_id = "world";
    relative_dis.header.stamp = ros::Time::now();
    relative_dis.header.seq = uwb_seq_count;
    uwb_seq_count++;
    uwb_dis_pub.publish(relative_dis);

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "uwb_recv");
    ros::NodeHandle nh;
    readParam<int>(nh, "swarm_ID",swarm_ID);
    std::string uav_name = "/uav"+to_string(swarm_ID);
    aruco_pose_pub = nh.advertise<nlink_parser::SwarmInfoStamped>(uav_name+"/uwb_recv_detected_aruco_pose", 1);
    uwb_dis_pub = nh.advertise<nlink_parser::UWBDisStamped>(uav_name+"/uwb_dis_stamped", 1);
    ros::Subscriber uwb_recv_sub = nh.subscribe(uav_name+"/nlink_linktrack_nodeframe0", 2, uwb_recv_cb);
    ros::Subscriber uwb_dis_sub = nh.subscribe(uav_name+"/nlink_linktrack_nodeframe3", 2, uwb_dis_cb);
    ros::Subscriber uwb_loop_recv_sub = nh.subscribe(uav_name+"/nlink_linktrack_data_transmission", 1, uwb_loop_recv_cb);
    ros::spin();

    return 0;
}

