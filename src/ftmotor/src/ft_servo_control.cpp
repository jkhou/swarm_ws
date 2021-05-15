//
// Created by zph on 2021/1/7.
// usage: ft servo driver, read angle, write angle
// input: servo expect angle
// output:servo present angle
#include <ros/ros.h>
#include "SCServo.h"
#include <geometry_msgs/Point32.h>
#include <std_msgs/Int32.h>
#include <string>
#include <visualization_msgs/MarkerArray.h>
using namespace std;
// global variable
int swarm_ID = 0;
std::string uav_name = "/uav"+to_string(swarm_ID);
SCSCL ft_servo;
ros::Publisher ft_servo_angle_pub;
ros::Publisher ft_servo_rotate_ctrl_pub;
int init_zero_pos = 512;//middle point of servo, total 0-1023 mapping to 0-300 degree
int pos_offset = 0;
std::string usb_port_name = "/dev/ttyUSB0";
int baud_rate = 38400;
int pub_rate = 30;
int servo_control_speed_fast = 500;
int servo_control_speed_slow = 100;
int servo_control_speed_mid  = 300;
int ft_servo_rotate_speed = 300;
double ft_servo_rotate_duration = 0.2;
double ft_servo_cur_pos = 0;
double ft_servo_set_angle = 0;
double ft_servo_direction = M_PI/18;
double ft_servo_half_range = M_PI/180*150;//150 degree to radius
double ft_servo_resolution = 512/ft_servo_half_range;//servo step per radius
int  pos_weight[6] = {0,0,0,0,0,0};//weight for key pos, decide which pos the servo will stop and how long
int time_weight_level1 = 10;
int time_weight_level2 = 15;
int time_weight_level3 = 20;
int time_weight_level4 = 25;
int aruco_num = 0;


// tool func
template<typename T>
void readParam(ros::NodeHandle &nh, std::string param_name, T& loaded_param) {
    // template to read param from roslaunch
    const string& node_name = ros::this_node::getName();
    param_name = node_name + "/" + param_name;
    if (!nh.getParam(param_name, loaded_param)) {
        ROS_ERROR_STREAM("Failed to load " << param_name << ", use default value");
    }
    else{
        ROS_INFO_STREAM("Load " << param_name << " success");
    }
}

void loadRosParams(ros::NodeHandle &nh) {
    readParam<int>(nh, "swarm_ID", swarm_ID);
    readParam<std::string>(nh, "usb_port_name", usb_port_name);
    readParam<int>(nh, "baud_rate", baud_rate);
    readParam<int>(nh, "ft_servo_rotate_speed", ft_servo_rotate_speed);
    readParam<int>(nh, "pos_offset", pos_offset);
    readParam<int>(nh, "pub_rate", pub_rate);
    readParam<double>(nh, "ft_servo_rotate_duration", ft_servo_rotate_duration);

    uav_name = "/uav" + to_string(swarm_ID);
    init_zero_pos += pos_offset;
    //print params
    ROS_INFO_STREAM("swarm_ID = " << swarm_ID);
    ROS_INFO_STREAM("usb_port_name = " << usb_port_name);
    ROS_INFO_STREAM("baud_rate = " << baud_rate);
    ROS_INFO_STREAM("ft_servo_rotate_speed = " << ft_servo_rotate_speed);
    ROS_INFO_STREAM("pos_offset = " << pos_offset);
    ROS_INFO_STREAM("ft_servo_rotate_duration = " << ft_servo_rotate_duration);
    ROS_INFO_STREAM("pub_rate = " << pub_rate);
}

void spin_sleep(double time){
    if(time<0) return;
    auto time_begin = ros::Time::now();
    while(ros::Time::now()-time_begin<ros::Duration(time)){
        ros::Duration(0.02).sleep();
        ros::spinOnce();
    }
    return;
}

void ft_servo_rotate_to_marker_ctrl_cb(const ros::TimerEvent&){
    if(aruco_num>0){
//        ROS_INFO_STREAM_THROTTLE(1,"see aruco, wait!");
        spin_sleep(0.8*aruco_num);
    }
    geometry_msgs::Point32  ft_servo_rotate_ctrl_setpoint;
    ft_servo_set_angle += ft_servo_direction;
    if(ft_servo_set_angle > ft_servo_half_range-pos_offset/ft_servo_resolution){
        ft_servo_direction = -ft_servo_direction;
    }
    if(ft_servo_set_angle < -ft_servo_half_range-pos_offset/ft_servo_resolution){
        ft_servo_direction = -ft_servo_direction;
    }
    ft_servo_rotate_ctrl_setpoint.x = ft_servo_set_angle;
    ft_servo_rotate_ctrl_setpoint.y = ft_servo_rotate_speed;
    ft_servo_rotate_ctrl_pub.publish(ft_servo_rotate_ctrl_setpoint);
}

bool rotate_first_run = true;
bool rotate_cb_lock = false;
void ft_servo_rotate_ctrl_cb(const ros::TimerEvent&){
    //complicate rotate cmd, not use
    if(rotate_first_run){//first time of run,scan around
        rotate_first_run=false;
        ft_servo.WritePos(1, 0, 0, ft_servo_rotate_speed);
        spin_sleep(2);
        ft_servo.WritePos(1, 1024, 0, ft_servo_rotate_speed);
        spin_sleep(4);
        return;
    }
    if(rotate_cb_lock) return;
    if(ft_servo_cur_pos>=985){
        rotate_cb_lock = true;
        int pos_weight_copy[6];
        for(int i=0;i<6;i++){
            pos_weight_copy[i] = pos_weight[5-i];
            ROS_INFO_STREAM("weight = "<<pos_weight[5-i]);
            pos_weight[5-i] = 0; //clear
        }
        for(int i=0;i<6;i++){
            if(pos_weight_copy[i]<time_weight_level1){
                if(i==5){//reach the other end
                    ft_servo.WritePos(1, 1000-200*i, 0, ft_servo_rotate_speed);
                    spin_sleep(1);
                }
                continue;
            }
            if(pos_weight_copy[i]<time_weight_level2){
                ft_servo.WritePos(1, 1000-200*i, 0, ft_servo_rotate_speed);
                spin_sleep(1.5);
                continue;
            }
            if(pos_weight_copy[i]<time_weight_level3){
                ft_servo.WritePos(1, 1000-200*i, 0, ft_servo_rotate_speed);
                spin_sleep(2);
                continue;
            }
            if(pos_weight_copy[i]<time_weight_level4){
                ft_servo.WritePos(1, 1000-200*i, 0, ft_servo_rotate_speed);
                spin_sleep(2.5);
                continue;
            }
            if(pos_weight_copy[i]>=time_weight_level4){
                ft_servo.WritePos(1, 1000-200*i, 0, ft_servo_rotate_speed);
                spin_sleep(3);
                continue;
            }
        }
        rotate_cb_lock = false;

    }
    else{
        if(ft_servo_cur_pos<=30){
            rotate_cb_lock = true;
            int pos_weight_copy[6];
            for(int i=0;i<6;i++){
                pos_weight_copy[i] = pos_weight[i];
                ROS_INFO_STREAM("weight = "<<pos_weight[i]);
                pos_weight[i] = 0; //clear
            }
            for(int i=0;i<6;i++){
                if(pos_weight_copy[i]<time_weight_level1){
                    if(i==5){//reach the other end
                        ft_servo.WritePos(1, 200*i, 0, ft_servo_rotate_speed);
                        spin_sleep(1);
                    }
                    continue;
                }
                if(pos_weight_copy[i]<time_weight_level2){
                    ft_servo.WritePos(1, 200*i, 0, ft_servo_rotate_speed);
                    spin_sleep(1.5);
                    continue;
                }
                if(pos_weight_copy[i]<time_weight_level3){
                    ft_servo.WritePos(1, 200*i, 0, ft_servo_rotate_speed);
                    spin_sleep(2);
                    continue;
                }
                if(pos_weight_copy[i]<time_weight_level4){
                    ft_servo.WritePos(1, 200*i, 0, ft_servo_rotate_speed);
                    spin_sleep(2.5);
                    continue;
                }
                if(pos_weight_copy[i]>=time_weight_level4){
                    ft_servo.WritePos(1, 200*i, 0, ft_servo_rotate_speed);
                    spin_sleep(3);
                    continue;
                }
            }
            rotate_cb_lock = false;
        }
        else{
//            ROS_INFO_STREAM_THROTTLE(1,"within limit"<<ft_servo.ReadPos(-1));
        }
    }

}

void ft_servo_rotate_ctrl_concise_cb(const ros::TimerEvent&){
    //more concise version of rotate cmd
    if(rotate_first_run){//first time of run,scan around
        rotate_first_run=false;
        ft_servo.WritePos(1, 0, 0, ft_servo_rotate_speed);
        spin_sleep(2);
        return;
    }
    if(ft_servo.ReadPos(-1)>=985){
        //reach upper limit, reverse rotation
        ROS_INFO_STREAM_THROTTLE(2,"upper limit");
        spin_sleep(1);
        ft_servo.WritePos(1, 0, 0, ft_servo_rotate_speed);
    }
    else{
        if(ft_servo.ReadPos(-1)<=30){
            //reach lower limit, reverse rotation
            ROS_INFO_STREAM_THROTTLE(2,"lower limit");
            spin_sleep(1);
            ft_servo.WritePos(1, 1023, 0, ft_servo_rotate_speed);
        }
        else{
//            ROS_INFO_STREAM_THROTTLE(1,"within limit"<<ft_servo.ReadPos(-1));
        }
    }

    // prev version of rotate cmd
//    geometry_msgs::Point32  ft_servo_rotate_ctrl_setpoint;
//    ft_servo_set_angle += ft_servo_direction;
//    if(ft_servo_set_angle > ft_servo_half_range-pos_offset/ft_servo_resolution){
//        ft_servo_direction = -ft_servo_direction;
//    }
//    if(ft_servo_set_angle < -ft_servo_half_range-pos_offset/ft_servo_resolution){
//        ft_servo_direction = -ft_servo_direction;
//    }
//    ft_servo_rotate_ctrl_setpoint.x = ft_servo_set_angle;
//    ft_servo_rotate_ctrl_setpoint.y = ft_servo_rotate_speed;
//    ft_servo_rotate_ctrl_pub.publish(ft_servo_rotate_ctrl_setpoint);
}

void ft_servo_angle_pub_timer_cb(const ros::TimerEvent&){
    //read servo pos, speed, load
    std::cout<<"ready in read loop"<<std::endl;
    std::cout<<ft_servo.FeedBack(1)<<std::endl;
    if(ft_servo.FeedBack(1)!=-1){
        std::cout<<"in read loop"<<std::endl;
        geometry_msgs::Point32 ft_servo_angle;
        ft_servo_cur_pos = ft_servo.ReadPos(-1);
        ft_servo_angle.x = float((ft_servo_cur_pos - pos_offset) / ft_servo_resolution - ft_servo_half_range);
//        usleep(50);
        // ft_servo_angle.y = float(ft_servo.ReadSpeed(-1));
        // usleep(1000);
        // ft_servo_angle.z = float(ft_servo.ReadLoad(-1));
        // usleep(1000);
        ft_servo_angle_pub.publish(ft_servo_angle);
    }
}

void ft_servo_angle_ctrl_cb(const geometry_msgs::Point32& msg){
    // angle: -2.618 rad (150 degree) to 2.618 rad (150 degree) to 0~1023. 512 is treated is as center
    float expect_angle = msg.x;
    float expect_speed = msg.y;
    //check angle value
    double upper_pos_limit = ft_servo_half_range-pos_offset/ft_servo_resolution;
    if(expect_angle > upper_pos_limit){
        expect_angle = upper_pos_limit;
    }
    else{
        double lower_pos_limit = -ft_servo_half_range-pos_offset/ft_servo_resolution;
        if(expect_angle < lower_pos_limit){
            expect_angle = lower_pos_limit;
        }
    }
    // transfer angle degree to pos value 0-1023
    int expect_pos = (int)((expect_angle + ft_servo_half_range) * ft_servo_resolution) + pos_offset;
    if(expect_pos > 1023){
        expect_pos = 1023;
    }else if(expect_pos < 0){
        expect_pos = 0;
    }
    // check Velocity: 0-1500
    if(expect_speed > 1500){   //最高速度V=1500步/秒
        expect_speed = 1500;
    }else if(expect_speed < 0){
        expect_speed = 0;
    }
    ft_servo.WritePos(1, expect_pos, 0, expect_speed);
    usleep(400);
}

void aruco_num_cb(const  std_msgs::Int32 &msg){
    aruco_num = msg.data;
    return;
    int pos_index = ft_servo_cur_pos/100;
    switch (pos_index) {
        case 0:
            pos_weight[0]+= aruco_num;
            ROS_INFO_STREAM_THROTTLE(1, "pos 0 find marker num:"<<aruco_num/2);
            break;
        case 1:
        case 2:
            pos_weight[1]+= aruco_num;
            ROS_INFO_STREAM_THROTTLE(1, "pos 1 find marker num:"<<aruco_num/2);
            break;
        case 3:
        case 4:
            pos_weight[2]+= aruco_num;
            ROS_INFO_STREAM_THROTTLE(1, "pos 2 find marker num:"<<aruco_num/2);
            break;
        case 5:
        case 6:
            pos_weight[3]+= aruco_num;
            ROS_INFO_STREAM_THROTTLE(1, "pos 3 find marker num:"<<aruco_num/2);
            break;
        case 7:
        case 8:
            pos_weight[4]+= aruco_num;
            ROS_INFO_STREAM_THROTTLE(1, "pos 4 find marker num:"<<aruco_num/2);
            break;
        case 9:
        case 10:
            pos_weight[5]+= aruco_num;
            ROS_INFO_STREAM_THROTTLE(1, "pos 5 find marker num:"<<aruco_num/2);
            break;
        default:
            ROS_ERROR_STREAM_THROTTLE(1,"not belong to any pos weight");
    }
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "ft_servo_control",ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    // load param
    loadRosParams(nh);
    // open servo
    if (!ft_servo.begin(baud_rate, usb_port_name.c_str())) {
        ROS_ERROR_STREAM("Failed to open ft motor, exit!");
        return -1;
    }
    std::cout<<"print"<<std::endl;    
    std::cout<<baud_rate<<std::endl;
    std::cout<< usb_port_name.c_str()<<std::endl;
    //control servo to init pos
    ft_servo.WritePos(1, init_zero_pos, 0, servo_control_speed_fast);
    sleep(2);
    //ros pub and sub
    ft_servo_angle_pub = nh.advertise<geometry_msgs::Point32>(uav_name+"/ft_servo_angle", 1);
    ft_servo_rotate_ctrl_pub = nh.advertise<geometry_msgs::Point32>(uav_name+"/ft_servo_angle_ctrl", 1);
    ros:: Subscriber ft_servo_angle_ctrl_sub = nh.subscribe(uav_name+"/ft_servo_angle_ctrl", 1,ft_servo_angle_ctrl_cb);
    ros:: Subscriber aruco_num_sub = nh.subscribe(uav_name+"/detected_aruco_num",1, aruco_num_cb);
    ros::Timer ft_servo_rotate_ctrl_timer = nh.createTimer(ros::Duration(ft_servo_rotate_duration), ft_servo_rotate_to_marker_ctrl_cb);
    ros::Timer ft_servo_angle_pub_timer = nh.createTimer(ros::Duration(1.0/pub_rate), ft_servo_angle_pub_timer_cb);

    // ros main loop
    ros::Rate ros_loop(pub_rate);
    while(ros::ok()){
        ros::spinOnce();
        ros_loop.sleep();
    }
    ft_servo.end();
    return 0;

}
