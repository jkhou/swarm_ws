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
#include "nlink_parser/LinktrackNodeframe0.h"
using namespace std;
//global variable
bool isGS = false;//whether this node is run on ground station
ros::Publisher aruco_pose_pub;
//uwb 发送的数据格式
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
    //发布为marker点，可视化
    visualization_msgs::MarkerArray  aruco_markers;
    //同时收到多个uwb的数据
    for(int j=0; j<msg.nodes.size(); j++){
        if(msg.nodes[j].id<1 || msg.nodes[j].id>4) continue;//表示并非飞机上的uwb
        //解析数据
        const std::vector<unsigned char>& s = msg.nodes[j].data;
        SWARM_POS many_pos;
        memcpy((void*)(&many_pos), (void*)(s.data()), sizeof(SWARM_POS));
        //将位置变成marker点
        for(int i=0;i<4;i++){
            UAV_POS one_uav_pos = many_pos.poses[i];
            if (one_uav_pos.x==0) continue;//表示当前没有看到这个点
            visualization_msgs::Marker one_marker;// record and show pose
            one_marker.header.frame_id = "world";
            one_marker.header.stamp = ros::Time::now();
            //one_marker.header.seq = ids[i];
            one_marker.header.seq = ros_seq_count;
            ros_seq_count++;
            one_marker.id = i+1;
            one_marker.ns = "uav"+std::to_string(msg.nodes[j].id);
            one_marker.type = visualization_msgs::Marker::SPHERE;
            one_marker.action = visualization_msgs::Marker::ADD;
            one_marker.lifetime = ros::Duration(5);
            one_marker.color.g = 1;
            one_marker.color.a = 0.5;
            if(one_marker.id==msg.nodes[j].id){//说明是该无人机发的自己的T265定位，换个颜色显示
                one_marker.color.b = 1;
                one_marker.color.a = 1;
            }
            one_marker.scale.x = 0.1;
            one_marker.scale.y = 0.1;
            one_marker.scale.z = 0.1;
            one_marker.pose.position.x = one_uav_pos.x/trans_scale;
            one_marker.pose.position.y = one_uav_pos.y/trans_scale;
            one_marker.pose.position.z = one_uav_pos.z/trans_scale;
            aruco_markers.markers.push_back(one_marker);
            //aruco_pose_pub.publish(one_marker);
            // for view marker id
            visualization_msgs::Marker text_marker;// record and show pose
            text_marker.header.frame_id = "world";
            text_marker.header.stamp = ros::Time::now();
            text_marker.header.seq = ros_seq_count;
            ros_seq_count++;
            text_marker.id = 1000+one_marker.id;//+1000, avoid id conflict
            text_marker.ns = "uav"+std::to_string(msg.nodes[j].id);
            if(msg.nodes[j].id==one_marker.id){
                text_marker.text = std::to_string(one_marker.id);
            }
            else{
                text_marker.text = std::to_string(one_marker.id)+"-"+std::to_string(msg.nodes[j].id);
            }
            text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
            text_marker.action = visualization_msgs::Marker::ADD;
            text_marker.lifetime = ros::Duration(5);
            text_marker.color.r = 1;
            text_marker.color.a = 1;
            text_marker.scale.z = 0.15;
            text_marker.pose.position.x = one_uav_pos.x/trans_scale;
            text_marker.pose.position.y = one_uav_pos.y/trans_scale;
            text_marker.pose.position.z = one_uav_pos.z/trans_scale+0.1;//a little bit above marker
            aruco_markers.markers.push_back(text_marker);
        }
    }

    aruco_pose_pub.publish(aruco_markers);

    return;
    
}

//void uwb_loop_recv_cb(const std_msgs::StringConstPtr &msg) {
//    //解析自己发送的数据,用于测试
//    std::string s = msg->data;
//    SWARM_POS many_pos;
//    memcpy((void*)(&many_pos), (void*)(s.c_str()), sizeof(SWARM_POS));
//    //发布为marker点，可视化
//    visualization_msgs::MarkerArray  aruco_markers;
//    for(int i=0;i<4;i++){
//        UAV_POS one_uav_pos = many_pos.swarm_pos[i];
//        if (one_uav_pos.marker_id<0) continue;
//        visualization_msgs::Marker one_marker;// record and show pose
//        one_marker.header.frame_id = "uav"+std::to_string(0);
//        one_marker.header.stamp = ros::Time::now();
//        //one_marker.header.seq = ids[i];
//        one_marker.header.seq = ros_seq_count;
//        ros_seq_count++;
//        one_marker.id = one_uav_pos.marker_id;
//        one_marker.ns = "uav"+std::to_string(0);
//        one_marker.type = visualization_msgs::Marker::SPHERE;
//        one_marker.action = visualization_msgs::Marker::ADD;
//        one_marker.lifetime = ros::Duration(0.1);
//        one_marker.color.g = 1;
//        one_marker.color.a = 1;
//        one_marker.scale.x = 0.2;
//        one_marker.scale.y = 0.2;
//        one_marker.scale.z = 0.2;
//        one_marker.pose.position.x = one_uav_pos.x;
//        one_marker.pose.position.y = one_uav_pos.y;
//        one_marker.pose.position.z = one_uav_pos.z;
//        aruco_markers.markers.push_back(one_marker);
//        //aruco_pose_pub.publish(one_marker);
//        // for view marker id
//        visualization_msgs::Marker text_marker;// record and show pose
//        text_marker.header.frame_id = "uav"+std::to_string(0);
//        text_marker.header.stamp = ros::Time::now();
//        text_marker.header.seq = ros_seq_count;
//        ros_seq_count++;
//        text_marker.id = 1000+one_uav_pos.marker_id;//+1000, avoid id conflict
//        text_marker.ns = "uav"+std::to_string(0);
//        text_marker.text = std::to_string(one_uav_pos.marker_id);
//        text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
//        text_marker.action = visualization_msgs::Marker::ADD;
//        text_marker.lifetime = ros::Duration(0.1);
//        text_marker.color.r = 1;
//        text_marker.color.a = 1;
//        text_marker.scale.z = 0.15;
//        text_marker.pose.position.x = one_uav_pos.x+0.1;
//        text_marker.pose.position.y = one_uav_pos.y+0.1;
//        text_marker.pose.position.z = one_uav_pos.z+0.1;//a little bit above marker
//        aruco_markers.markers.push_back(text_marker);
//    }
//    aruco_pose_pub.publish(aruco_markers);
//
//    return;
//}

int main(int argc, char **argv) {
    ros::init(argc, argv, "gs_uwb_recv");
    ros::NodeHandle nh;
    aruco_pose_pub = nh.advertise<visualization_msgs::MarkerArray>("/uwb_recv_detected_aruco_pose", 1);
    ros::Subscriber uwb_recv_sub = nh.subscribe("/nlink_linktrack_nodeframe0", 1000, uwb_recv_cb);
    //ros::Subscriber uwb_loop_recv_sub = nh.subscribe("/nlink_linktrack_data_transmission", 1000, uwb_loop_recv_cb);

    ros::spin();

    return 0;
}

