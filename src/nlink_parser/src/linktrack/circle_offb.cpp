//
// Created by zph on 2021/4/15.
//
//

#include <ros/ros.h>
#include "PID.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <geometry_msgs/TwistStamped.h>
#include <string>
#include <ros/package.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <nlink_parser/SwarmInfoStamped.h>
using namespace Eigen;
using namespace std;

// global variable
mavros_msgs::State uav_cur_state;//无人机当前状态
geometry_msgs::PoseStamped uav_cur_pose,uav_global_pose;//无人机当前位置+姿态
geometry_msgs::Point swarm_init_pos[4],swarm_info_pos[4];//无人机初始位置,无人机集群通信得到的全体位置
sensor_msgs::Imu uav_cur_imu;//无人机当前imu数据
geometry_msgs::Vector3 uav_cur_rpy;//无人机当前姿态，欧拉角表示
geometry_msgs::TwistStamped uav_cur_vel;//无人机当前速度
PID PIDVX, PIDVY, PIDVZ;    //声明PID类,速度环
vector<float> PIDPxyz(3);//PID参数位置环的p
float CircleKpxy = 1, CircleKvxy = 1, CircleKpz = 1, CircleKvz = 1;//画圆的位置环和速度环比例参数
float CircleR = 1, CircleW = 0.2;//画圆的半径和角速度
float theta0 = 0;//画圆初始相位
float formationKpxy = 0, formationKpz = 0;//队形控制的P参数
float StartW = 0.1, T_hold = 30,T_reach = 10,T_stop = 5;//实验过程中起始角速度，到达最高角速度所需的时间，维持最高角速度的时间，从最高角速度刹车的时间
double last_t_gap = 0;//开始轨迹追踪的时间
double theta_add = 0;//轨迹追踪的相位累积
bool start_I = false;//是否开始积分，只有在offboard控制姿态的情况下才开始积分
bool first_PID = true;//是否刚刚进入PID轨迹追踪，是的话记录积分时间的起点
ros::Time PID_begin_time;
float uav_init_x = 0;
float uav_init_y = 0;
float hover_height=1;
float thrust_limit = 0.9;
float hover_thrust = 0.3;
int swarm_ID = 1;
std::string uav_name = "/uav"+to_string(swarm_ID);
int ctrl_rate = 30;
int aruco_num = 0;
string traj_csv_name = "/param/circle_flat.csv";
bool repeat_path = false;
ros::Publisher exp_pose_pub;
ros::Publisher exp_vel_pub;
ros::Publisher exp_acc_pub;
ros::Publisher control_acc_pub;
ros::Publisher control_z_pub;


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
    readParam<float>(nh, "CircleKpxy", CircleKpxy);
    readParam<float>(nh, "CircleKvxy", CircleKvxy);
    readParam<float>(nh, "CircleKpz", CircleKpz);
    readParam<float>(nh, "CircleKvz", CircleKvz);
    readParam<float>(nh, "CircleR", CircleR);
    readParam<float>(nh, "CircleW", CircleW);
    readParam<float>(nh, "formationKpxy", formationKpxy);
    readParam<float>(nh, "formationKpz", formationKpz);
    readParam<float>(nh, "StartW", StartW);
    readParam<float>(nh, "T_hold", T_hold);
    readParam<float>(nh, "T_reach", T_reach);
    readParam<float>(nh, "T_stop", T_stop);
    readParam<float>(nh, "hover_thrust", hover_thrust);
    readParam<float>(nh, "hover_height", hover_height);
    readParam<string>(nh, "traj_csv_name",traj_csv_name);
    readParam<bool>(nh, "repeat_path",repeat_path);
    //read param from roslaunch
    vector<float> poses(12);
    readParam<vector<float>>(nh, "swarm_init_pos", poses);
    // give to global variable
    for (int i = 0; i < 4; i++) {
        //对4个无人机依次赋值初始位置
        swarm_init_pos[i].x = poses[3*i];
        swarm_init_pos[i].y = poses[3*i+1];
        swarm_init_pos[i].z = poses[3*i+2];
    }
    //画圆初始相位确定
    switch (swarm_ID){
        case 1: theta0 = 0       ;break;
        case 2: theta0 = M_PI*0.5;break;
        case 3: theta0 = M_PI    ;break;
        case 4: theta0 = M_PI*1.5;break;
        default:
            ROS_ERROR_STREAM("Unexpected swarm_ID !");
    }

    vector<float> PIDVxyz(9);
    readParam<vector<float>>(nh, "PIDVxyz", PIDVxyz);
    readParam<vector<float>>(nh, "PIDPxyz", PIDPxyz);
    /// 设置速度环PID参数 比例参数 积分参数 微分参数
    PIDVX.setPID(PIDVxyz[0], PIDVxyz[1], PIDVxyz[2]);
    PIDVY.setPID(PIDVxyz[3], PIDVxyz[4], PIDVxyz[5]);
    PIDVZ.setPID(PIDVxyz[6], PIDVxyz[7], PIDVxyz[8]);
    // 设置速度环积分上限 控制量最大值 误差死区
    PIDVX.set_sat(6, 10, 0);
    PIDVY.set_sat(2, 3, 0);
    PIDVZ.set_sat(2, 5, 0);
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
    ROS_INFO_STREAM("hover_thrust = " << hover_thrust);
    ROS_INFO_STREAM("CircleW = " << CircleW);
    ROS_INFO_STREAM("StartW = " << StartW);
    ROS_INFO_STREAM("init pos = (" << swarm_init_pos[swarm_ID-1].x<<","<<swarm_init_pos[swarm_ID-1].y<<")");
//    ROS_INFO_STREAM("uav_init_pos = "<<uav_init_x<<","<<uav_init_y);
}

/**
 * 将欧拉角转化为四元数
 * @param roll
 * @param pitch
 * @param yaw
 * @return 返回四元数
 */
geometry_msgs::Quaternion euler2quaternion(float roll, float pitch, float yaw)
{
    geometry_msgs::Quaternion temp;
    temp.w = cos(roll/2)*cos(pitch/2)*cos(yaw/2) + sin(roll/2)*sin(pitch/2)*sin(yaw/2);
    temp.x = sin(roll/2)*cos(pitch/2)*cos(yaw/2) - cos(roll/2)*sin(pitch/2)*sin(yaw/2);
    temp.y = cos(roll/2)*sin(pitch/2)*cos(yaw/2) + sin(roll/2)*cos(pitch/2)*sin(yaw/2);
    temp.z = cos(roll/2)*cos(pitch/2)*sin(yaw/2) - sin(roll/2)*sin(pitch/2)*cos(yaw/2);
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
geometry_msgs::Vector3 quaternion2euler(float x, float y, float z, float w)
{
    geometry_msgs::Vector3 temp;
    temp.x = atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (x * x + y * y));
    temp.y = asin(2.0 * (w * y - z * x));
    temp.z = atan2(2.0 * (w * z + x * y), 1.0 - 2.0 * (y * y + z * z));
    return temp;
}

void circle_controller(mavros_msgs::AttitudeTarget& att_thrust){
    //计算当前时间距离积分起始时间的间隔
    ros::Duration duration = ros::Time::now() - PID_begin_time;
    double t_gap = duration.toSec();
    double delta_t = t_gap - last_t_gap;
    last_t_gap = t_gap;
    //发布的消息
    geometry_msgs::PoseStamped exp_pose;
    geometry_msgs::TwistStamped exp_vel;
    geometry_msgs::TwistStamped exp_acc;
    geometry_msgs::TwistStamped control_acc;
    geometry_msgs::TwistStamped control_z;
    //为了防止初始角速度给的过大造成过冲，对角速度进行递增控制,控制依据是距离实验开始的时间，从慢到快，再到慢
    float W=CircleW;//实际控制的角速度
    if(CircleW>StartW){
        //设定的最高角速度大于初始角速度，从较低的角速度开始
        if(t_gap<=T_reach){//处于初始加速阶段
            W = StartW+(CircleW-StartW)*t_gap/T_reach;
        }
        else{
            if(t_gap<=(T_reach+T_hold)){//处于高速阶段
                W = CircleW;
            }
            else{
                if(t_gap<=(T_reach+T_hold+T_stop)){//处于减速阶段
                    W = CircleW-(CircleW-StartW)*(t_gap-T_reach-T_hold)/T_stop;
                    if(W<0) W = 0;
                }
                else{//处于低速阶段
                    W = StartW;
                }
            }
        }
    }
    else{//设定的期望角速度很低，直接给
        W = CircleW;
    }
//    ROS_INFO_STREAM_THROTTLE(0.1, "W="<<W);
//    ROS_INFO_STREAM_THROTTLE(0.1, "t_gap="<<t_gap);
//    ROS_INFO_STREAM_THROTTLE(0.1, "W*t_gap+theta0="<<W*t_gap+theta0);
    //计算相位
    theta_add += delta_t * W;
    //期望位置，解析解
    exp_pose.pose.position.x = CircleR*cos(theta_add+theta0);
    exp_pose.pose.position.y = CircleR*sin(theta_add+theta0);
    exp_pose.pose.position.z = hover_height;
    //期望速度，解析解求导
    exp_vel.twist.linear.x = -CircleR*W*sin(theta_add+theta0);
    exp_vel.twist.linear.y =  CircleR*W*cos(theta_add+theta0);
    exp_vel.twist.linear.z = 0;
    //期望加速度，解析解求导
    exp_acc.twist.linear.x = -CircleR*W*W*cos(theta_add+theta0);
    exp_acc.twist.linear.y = -CircleR*W*W*sin(theta_add+theta0);
    exp_acc.twist.linear.z = 0;
    //计算编队误差
    double swarm_pos_err_x = 0, swarm_pos_err_y = 0, swarm_pos_err_z = 0;
    if(swarm_info_pos[(swarm_ID-2+4)%4].x != 0){//上一个uav有值，可以计算误差
        swarm_pos_err_x += (CircleR*cos(theta_add+theta0-M_PI/2)-exp_pose.pose.position.x) - swarm_info_pos[(swarm_ID-2+4)%4].x; //期望差-实际差
        swarm_pos_err_y += (CircleR*sin(theta_add+theta0-M_PI/2)-exp_pose.pose.position.y) - swarm_info_pos[(swarm_ID-2+4)%4].y; //期望差-实际差
        swarm_pos_err_z += swarm_info_pos[(swarm_ID-2+4)%4].z;
    }
    if(swarm_info_pos[(swarm_ID+4)%4].x != 0){//下一个 uav有值，可以计算误差
        swarm_pos_err_x += (CircleR*cos(theta_add+theta0+M_PI/2)-exp_pose.pose.position.x) - swarm_info_pos[(swarm_ID+4)%4].x;
        swarm_pos_err_y += (CircleR*sin(theta_add+theta0+M_PI/2)-exp_pose.pose.position.y) - swarm_info_pos[(swarm_ID+4)%4].y;
        swarm_pos_err_z += swarm_info_pos[(swarm_ID+4)%4].z;
    }


    //实际给定的加速度，误差反馈
    double ax = control_acc.twist.linear.x = exp_acc.twist.linear.x
                                           + CircleKpxy*(exp_pose.pose.position.x - uav_global_pose.pose.position.x)
                                           + CircleKvxy*(exp_vel.twist.linear.x - uav_cur_vel.twist.linear.x)
                                           + formationKpxy*swarm_pos_err_x;
    double ay = control_acc.twist.linear.y = exp_acc.twist.linear.y
                                           + CircleKpxy*(exp_pose.pose.position.y - uav_global_pose.pose.position.y)
                                           + CircleKvxy*(exp_vel.twist.linear.y - uav_cur_vel.twist.linear.y)
                                           + formationKpxy*swarm_pos_err_y;
    double az = control_acc.twist.linear.z = exp_acc.twist.linear.z
                                           + CircleKpz*(exp_pose.pose.position.z - uav_global_pose.pose.position.z)
                                           + CircleKvz*(exp_vel.twist.linear.z - uav_cur_vel.twist.linear.z)
                                           + formationKpz*swarm_pos_err_z;
    control_z.twist.linear.x = CircleKpz*(exp_pose.pose.position.z - uav_global_pose.pose.position.z);
    control_z.twist.linear.y = CircleKvz*(exp_vel.twist.linear.z - uav_cur_vel.twist.linear.z);
    control_z.twist.linear.z = formationKpz*swarm_pos_err_z;

    //z方向采用PID控制器调包
//    float error_z = hover_height - uav_global_pose.pose.position.z + formationKpz*swarm_pos_err_z;//计算位置环误差
//    float vel_zd = PIDPxyz[2] * error_z;//计算指定速度误差
//    float error_vz = vel_zd - uav_cur_vel.twist.linear.z;//计算误差
//    PIDVZ.start_intergrate_flag = true;
//    if(start_I == false){
//        PIDVZ.start_intergrate_flag = false;
//    }
//    PIDVZ.add_error(error_vz, t_gap);
//    PIDVZ.pid_output();
//    double az  = PIDVZ.Output;
    //给时间戳，发布消息
    exp_pose.header.stamp = exp_vel.header.stamp = exp_acc.header.stamp = control_acc.header.stamp = control_z.header.stamp = ros::Time::now();
    exp_pose_pub.publish(exp_pose);
    exp_vel_pub.publish(exp_vel);
    exp_acc_pub.publish(exp_acc);
    control_acc_pub.publish(control_acc);
    control_z_pub.publish(control_z);
    //计算控制量
    double roll = asin(-ay/sqrt(ax*ax+ay*ay+pow(az+9.8,2)));
    double pitch = atan(ax/(az+9.8));
    double yaw = 0;
    double thrust  = sqrt(ax*ax+ay*ay+pow(az+9.8,2))/9.8*hover_thrust;   //目标推力值
    if(thrust>thrust_limit) thrust=thrust_limit;
    att_thrust.thrust = thrust;
    att_thrust.orientation = euler2quaternion(roll, pitch, yaw);
    att_thrust.header.stamp = ros::Time::now();
}

void pix_controller(mavros_msgs::AttitudeTarget& att_thrust,  geometry_msgs::PoseStamped traj_pose){
    //计算当前时间距离积分起始时间的间隔
    float t_gap = ros::Time::now().toSec() - PID_begin_time.toSec();
    //位 置 环
    //计算误差
    float error_x = traj_pose.pose.position.x - uav_cur_pose.pose.position.x;
    float error_y = traj_pose.pose.position.y - uav_cur_pose.pose.position.y;
    float error_z = traj_pose.pose.position.z - uav_cur_pose.pose.position.z;
    //std::cout << "error: x：" << error_x << "\ty：" << error_y << "\tz：" << error_z << std::endl;
    //计算指定速度误差
    float vel_xd = PIDPxyz[0] * error_x;
    float vel_yd = PIDPxyz[1] * error_y;
    float vel_zd = PIDPxyz[2] * error_z;

    //速 度 环
    //积分标志位.未进入OFFBOARD时,不累积积分项;进入OFFBOARD时,开始积分.
    PIDVX.start_intergrate_flag = true;
    PIDVY.start_intergrate_flag = true;
    PIDVZ.start_intergrate_flag = true;
    if(start_I == false){
        PIDVX.start_intergrate_flag = false;
        PIDVY.start_intergrate_flag = false;
        PIDVZ.start_intergrate_flag = false;
    }
    //计算误差
    float error_vx = vel_xd - uav_cur_vel.twist.linear.x;
    float error_vy = vel_yd - uav_cur_vel.twist.linear.y;
    float error_vz = vel_zd - uav_cur_vel.twist.linear.z;
    //传递误差
    PIDVX.add_error(error_vx, t_gap); //把error放到list中
    PIDVY.add_error(error_vy, t_gap);
    PIDVZ.add_error(error_vz, t_gap);
    //计算输出
    PIDVX.pid_output();
    PIDVY.pid_output();
    PIDVZ.pid_output();
    //转换成相应格式
    double roll = asin(-PIDVY.Output/sqrt(pow(PIDVX.Output,2)+pow(PIDVY.Output,2)+pow(PIDVZ.Output+9.8,2)));
    double pitch = atan(PIDVX.Output/(PIDVZ.Output+9.8));
    double yaw = 0;
    double thrust  = (float)sqrt(pow(PIDVX.Output,2)+pow(PIDVY.Output,2)+pow(PIDVZ.Output+9.8,2))/9.8*hover_thrust;   //目标推力值
    if(thrust>thrust_limit) thrust=thrust_limit;
    att_thrust.thrust = thrust;
    att_thrust.orientation = euler2quaternion(roll, pitch, yaw);
    att_thrust.header.stamp = ros::Time::now();
}

// CB function
void uav_state_cb(const mavros_msgs::State::ConstPtr& msg){
    uav_cur_state = *msg;
}

void uav_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    uav_cur_pose = *msg;
    geometry_msgs::PoseStamped tmp = *msg;
    tmp.pose.position.x += swarm_init_pos[swarm_ID-1].x;
    tmp.pose.position.y += swarm_init_pos[swarm_ID-1].y;
    uav_global_pose = tmp;
}

void uav_vel_cb(const geometry_msgs::TwistStamped::ConstPtr& msg){
    uav_cur_vel = *msg;
}

//void uav_imu_cb(const sensor_msgs::Imu::ConstPtr &msg){
//    uav_cur_imu = *msg;
//    uav_cur_rpy = quaternion2euler(uav_cur_imu.orientation.x, uav_cur_imu.orientation.y, uav_cur_imu.orientation.z, uav_cur_imu.orientation.w);
//}

void swarm_info_cb(const nlink_parser::SwarmInfoStamped &msg){
    for(int i=1; i<=4; i++){
        if(i==(swarm_ID)) continue;//计算相对其他无人机的位置，不包括自己的位置
        if(msg.poses[5*i-5].x!=0 && msg.poses[5*i-5].y!=0){
            //有T265的数据,记录相对位置
            swarm_info_pos[i-1].x = msg.poses[5*i-5].x + swarm_init_pos[i-1].x - uav_global_pose.pose.position.x;//计算全局相对位置
            swarm_info_pos[i-1].y = msg.poses[5*i-5].y + swarm_init_pos[i-1].y - uav_global_pose.pose.position.y;
            swarm_info_pos[i-1].z = msg.poses[5*i-5].z - uav_global_pose.pose.position.z;

        }
        else{
            swarm_info_pos[i-1].x = 0;//取值0，表示没有信息
            swarm_info_pos[i-1].y = 0;
            swarm_info_pos[i-1].z = 0;
        }
    }

}

int main (int argc, char** argv) {
    // ros init
    ros::init(argc, argv, "circle_offb", ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    // load param
    loadRosParams(nh);
    std::string pkg_path = ros::package::getPath("nlink_parser");
    std::vector<std::vector<double>> csv_traj = read_csv_traj(pkg_path + traj_csv_name);
    //ros pub and sub
    //sub
    ros::Subscriber uav_state_sub = nh.subscribe<mavros_msgs::State>
            (uav_name+"/mavros/state", 1, uav_state_cb);
    ros::Subscriber uav_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>
            (uav_name+"/mavros/vision_pose/pose", 1, uav_pose_cb);
    ros::Subscriber uav_vel_sub = nh.subscribe<geometry_msgs::TwistStamped>
            (uav_name+"/mavros/local_position/velocity_local_smoothed", 1, uav_vel_cb);
    ros::Subscriber swarm_info_sub = nh.subscribe(uav_name+"/uwb_recv_detected_aruco_pose", 1, swarm_info_cb);
//    ros::Subscriber uav_imu_sub = nh.subscribe<sensor_msgs::Imu>
//            (uav_name+"/mavros/imu/data", 1, uav_imu_cb);
    // pub
    ros::Publisher offb_setpoint_pub = nh.advertise<geometry_msgs::PoseStamped>
            (uav_name+"/mavros/setpoint_position/local", 1);
    ros::Publisher offb_atti_pub = nh.advertise<mavros_msgs::AttitudeTarget>
             (uav_name+"/mavros/setpoint_raw/attitude", 1);
    exp_pose_pub = nh.advertise<geometry_msgs::PoseStamped>
            (uav_name+"/mavros/exp_pose/pose", 1);
    exp_vel_pub = nh.advertise<geometry_msgs::TwistStamped>
            (uav_name+"/mavros/exp_vel/vel", 1);
    exp_acc_pub = nh.advertise<geometry_msgs::TwistStamped>
            (uav_name+"/mavros/exp_acc/acc", 1);
    control_acc_pub = nh.advertise<geometry_msgs::TwistStamped>
            (uav_name+"/mavros/control_acc/acc", 1);
    control_z_pub = nh.advertise<geometry_msgs::TwistStamped>
            (uav_name+"/mavros/control_z/acc", 1);

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
    bool first_offb = true;//用于记录初次切入offboard模式的时间点，以此同步多架飞机运动开始的时间
    geometry_msgs::PoseStamped pose_offb_hover;//pose to hover in offboard mode
    pose_offb_hover = uav_cur_pose;
    int traj_index = 0;
    double t_init_move = 0;

    //main ctrl loop
    while(ros::ok()) {
        if (uav_cur_state.armed) {
            if (uav_cur_state.mode == "OFFBOARD") {
                if(first_offb){
                    t_init_move = int(ros::Time::now().toSec()/10)*10+25;//初始运动时间为当前时间点10位数取整的N秒后，这样可以避免集群个位数秒的偏差
                    first_offb = false;
                }
                if(!takeoff){
                    //take off to some height
                    geometry_msgs::PoseStamped takeoff_pose;
//                    takeoff_pose.pose.position.x = uav_cur_pose.pose.position.x;
//                    takeoff_pose.pose.position.y = uav_cur_pose.pose.position.y;
                    takeoff_pose.pose.position.x = 0;
                    takeoff_pose.pose.position.y = 0;
                    takeoff_pose.pose.position.z = hover_height;
                    double err = 0.02;
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
//                    for(int i = 5; ros::ok() && i > 0; --i){
//                        offb_setpoint_pub.publish(pose_before_offb);
//                        ros::spinOnce();
//                        ctrl_loop.sleep();
//                    }
                    just_offb = false;
                    pose_offb_hover = pose_before_offb;
                }
                // has take off, into offboard control
                ROS_INFO_STREAM_THROTTLE(1, uav_name+" in Offboard cmd");
                //判断时间点是否达到期望开始运动的时刻，没有的话原地悬停
                if(ros::Time::now().toSec()<t_init_move){
                    //还不到运动时间，原地悬停
                    offb_setpoint_pub.publish(pose_offb_hover);
                }
                else{//到了运动时间，开始集群运动
                    if(first_PID){
                        //刚刚开始PID轨迹追踪
                        start_I = true;//PID的积分项可以开始计算了
                        PID_begin_time = ros::Time::now();
                        first_PID = false;
                    }
                    if(traj_index+1 < csv_traj.size()){

//                    //选项1：悬停测试
//                    geometry_msgs::PoseStamped traj_pose;
//                    traj_pose.pose.position.x = pose_before_offb.pose.position.x;
//                    traj_pose.pose.position.y = pose_before_offb.pose.position.y;
//                    traj_pose.pose.position.z = hover_height;
//                    traj_pose.header.frame_id = uav_name;
//                    traj_pose.header.stamp = ros::Time::now();
//                    //用姿态控制无人机
//                    mavros_msgs::AttitudeTarget att_thrust; //最终发布的消息：角度+油门
//                    pix_controller(att_thrust, traj_pose);//计算与目标位置的偏差，返回控制量
//                    offb_atti_pub.publish(att_thrust);
//                    ROS_INFO_STREAM_THROTTLE(0.1, "thrust:"+to_string(att_thrust.thrust));
//                    //offb_setpoint_pub.publish(traj_pose);
//                    pose_offb_hover = uav_cur_pose;

                        //选项2：轨迹追踪
//                    geometry_msgs::PoseStamped traj_pose;
//                    traj_pose.pose.position.x = csv_traj[traj_index][0] + pose_before_offb.pose.position.x;
//                    traj_pose.pose.position.y = csv_traj[traj_index][1] + pose_before_offb.pose.position.y;
//                    traj_pose.pose.position.z = hover_height + csv_traj[traj_index][2];
//                    traj_pose.header.frame_id = uav_name;
//                    traj_pose.header.stamp = ros::Time::now();
//                    offb_setpoint_pub.publish(traj_pose);
//                    pose_offb_hover = uav_cur_pose;
//                    traj_index++;
//                    //用姿态控制无人机
//                    mavros_msgs::AttitudeTarget att_thrust; //最终发布的消息：角度+油门
//                    pix_controller(att_thrust, traj_pose);//计算与目标位置的偏差，返回控制量
//                    offb_atti_pub.publish(att_thrust);
//                    pose_offb_hover = uav_cur_pose;
//                    traj_index++;

                        //选项3：sin函数表示的画圆
                        //用姿态控制无人机
                        mavros_msgs::AttitudeTarget att_thrust; //最终发布的消息：角度+油门
                        circle_controller(att_thrust);//计算与目标位置的偏差，返回控制量
                        offb_atti_pub.publish(att_thrust);
                        pose_offb_hover = uav_cur_pose;

                    }
                    else{
                        if(repeat_path){
                            traj_index=0;//从头开始
                        }
                        else{
                            //悬停
                            offb_setpoint_pub.publish(pose_offb_hover);
                            //姿态控制的积分环节停止
                            first_PID = true;
                            start_I = false;
                        }
                    }
                }



            }
            else{//not offb
                ROS_INFO_STREAM_THROTTLE(1, uav_name+" waiting for Offboard cmd");
                offb_setpoint_pub.publish(uav_cur_pose);
                pose_before_offb = uav_cur_pose;
                just_offb = true;
                first_PID = true;
                start_I = false;
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
