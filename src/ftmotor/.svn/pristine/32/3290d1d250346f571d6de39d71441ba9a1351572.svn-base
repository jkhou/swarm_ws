#include <ros/ros.h> 
#include "SCServo.h"
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <geometry_msgs/Point32.h>
#include <control_msgs/JointControllerState.h>

SCSCL sc;
ros::Publisher po_ve_pub, po_ve_pub2;

int offset = -25;
int pos_sp = 512;

void commandsCallback(const geometry_msgs::Point32& msg)
{
    // Position: -2.618 rad (150 degree) to 2.618 rad (150 degree) to 0~1023. 512 is treated is as center
    float pos_sp_ori = msg.x;
    float vel_sp_ori = msg.y;

    if(pos_sp_ori > M_PI){
        pos_sp_ori-= 2*M_PI;
    }else if(pos_sp_ori < -M_PI){
        pos_sp_ori += 2*M_PI;
    }

    if(pos_sp_ori > 2.618){
        pos_sp_ori = 2.618;
    }else if(pos_sp_ori < -2.618){
        pos_sp_ori = -2.618;
    }

    pos_sp = (int)((pos_sp_ori + 2.618) * 195.38) + offset;
    if(pos_sp > 1023){
        pos_sp = 1023;
    }else if(pos_sp < 0){
        pos_sp = 0;
    }

    // Velocity: 0-1 to 0-1500
    int vel_sp = (int)(vel_sp_ori * 1500);
    if(vel_sp > 1500){   //最高速度V=1500步/秒
        vel_sp = 1500;
    }else if(vel_sp < 0){
        vel_sp = 0;
    }

    sc.WritePos(1, pos_sp, 0, vel_sp);
    usleep(2e6);
}


int main (int argc, char** argv) 
{
    ros::init(argc, argv, "small_motor_driver");

    if(!sc.begin(38400, "/dev/ttyS0")){
        std::cout<< "Failed to init scscl motor!"<<std::endl;
        return -1;
    }

    //声明节点句柄
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/gimbal_commands", 1, commandsCallback);
    // publisher
    po_ve_pub = nh.advertise<geometry_msgs::Point32>("place_velocity_info", 1);
    po_ve_pub2 = nh.advertise<control_msgs::JointControllerState>("place_velocity_info_joint_state", 1);


    geometry_msgs::Point32 pvload_msg;
    control_msgs::JointControllerState position_msg;

    geometry_msgs::Point32 init_point;
    init_point.x = 0;
    init_point.y = 0;
    init_point.z = 0;
    commandsCallback(init_point);

    usleep(1e6);

    ros::Rate loop_rate(100);  //ori 40
    while(ros::ok()) 
    {	
        float fake_pose = (pos_sp - offset) / 195.38 - 2.618;
        pvload_msg.x = fake_pose;
        pvload_msg.y = 0;
        pvload_msg.y = 0;
        po_ve_pub.publish(pvload_msg);

        position_msg.process_value = fake_pose;
        position_msg.header.frame_id = "world";
        position_msg.header.stamp = ros::Time::now();
        po_ve_pub2.publish(position_msg);

        loop_rate.sleep();
        ros::spinOnce();
    } 
    sc.end();
    return 0;
}
