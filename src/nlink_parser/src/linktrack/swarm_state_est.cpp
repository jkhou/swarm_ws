//
// Created by zph on 2021/4/7.
//

#include "ceres/ceres.h"
#include "glog/logging.h"
#include <iostream>
#include <fstream>
#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>
#include <nlink_parser/SwarmInfoStamped.h>
#include <nlink_parser/UWBDisStamped.h>
#include <nlink_parser/SwarmPosStamped.h>
#include <boost/bind.hpp>
#include <list>
#include <cstdio>
#include <ctime>


using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::CauchyLoss;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;
using namespace  std;
using namespace message_filters;
//global variable
int swarm_ID=0;
nlink_parser::UWBDisStamped cur_uwb_dis,uwb_dis,prev_uwb_dis;
geometry_msgs::Point swarm_cur_pos[4], swarm_pre_pos[4], swarm_pre_vel[4],swarm_init_pos[4];
ros::Publisher swarm_fusion_pos_pub;
ros::Time t_last_cb;//回调时间，用于计算两个估计的时间差，计算预测值
int swarm_fusion_pos_seq_count=0;
bool save_csv = true;
string path_csv = "/home/up/rosbag/";
//进行融合的权重
float w_t265 = 1;
float w_a1 = 1;
float w_a1hop = 1;
float w_a2hop = 1;
float w_pred = 1;
float w_uwb = 1;
nlink_parser::SwarmPosStamped swarm_pred,swarm_vio,swarm_aruco0,swarm_aruco1,swarm_aruco2;//记录处理融合过程中的分项数据
//ceres求解器的一些函数定义
struct PointResidual {
    PointResidual(double x, double y, double z, double w)
            : x_(x), y_(y), z_(z), w_(w) {}

    template <typename T>
    bool operator()(const T* const px, const T* const py, const T* const pz, T* residual) const {
        residual[0] = w_*(x_ - px[0]);
        residual[1] = w_*(y_ - py[0]);
        residual[2] = w_*(z_ - pz[0]);
        return true;
    }

private:
    // Observations for a point.
    const double x_;
    const double y_;
    const double z_;
    const double w_;//权重
};

struct UWBResidual {
    UWBResidual(double d, double w)
            : d_(d), w_(w) {}

    template <typename T>
    bool operator()(const T* const px, const T* const py, const T* const pz, T* residual) const {
        residual[0] = w_*(d_ - sqrt(px[0]*px[0] + py[0]*py[0] + pz[0]*pz[0]));
        return true;
    }

private:
    // Observations for a point.
    const double d_;//UWB测量得到的距离
    const double w_;//权重
};

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

void callback(const nlink_parser::SwarmInfoStampedConstPtr &swarm_info, const nlink_parser::UWBDisStampedConstPtr &uwb_dis)
{
    // Solve all of perception here...
}

void uwb_dis_cb(const nlink_parser::UWBDisStamped &msg) {
    cur_uwb_dis = msg;
}

void swarm_info_cb(const nlink_parser::SwarmInfoStamped &msg) {
    ros::Time t_begin = ros::Time::now();//时间
    uwb_dis = cur_uwb_dis;//记录同一时刻uwb的距离信息

    for(int i = 1;i<=4;i++){
        if(i==(swarm_ID)) continue;//估计相对其他无人机的位置，不包括自己的位置
        //此时对应求解第i个无人机的位置
        //第一项，vio的相对位置
        geometry_msgs::Point p_t265;
        int t265_count=0;
        if(msg.poses[5*i-5].x!=0 && msg.poses[5*i-5].y!=0){
            //有T265的数据,记录相对位置
            t265_count = 1;
            p_t265.x = msg.poses[5*i-5].x - msg.poses[5*swarm_ID-5].x + swarm_init_pos[i-1].x;//加上初始偏差,此时认为T265发布的是局部位置
            p_t265.y = msg.poses[5*i-5].y - msg.poses[5*swarm_ID-5].y + swarm_init_pos[i-1].y;
            p_t265.z = msg.poses[5*i-5].z - msg.poses[5*swarm_ID-5].z + swarm_init_pos[i-1].z;

        }
        //第二项，aruco观测结果
        //直接观察的结果
        int aruco_direct_count = 0;
        geometry_msgs::Point p_aruco_direct_mean;
        ////直接观察的结果，看到i
        if(msg.poses[4*swarm_ID+i-5].x!=0) {
            aruco_direct_count++;
            p_aruco_direct_mean.x += msg.poses[4*swarm_ID+i-5].x;
            p_aruco_direct_mean.y += msg.poses[4*swarm_ID+i-5].y;
            p_aruco_direct_mean.z += msg.poses[4*swarm_ID+i-5].z;
        }
        ////直接观察的结果，被i看到
        if(msg.poses[4*i+swarm_ID-5].x!=0){
            //相对位置，反向
            aruco_direct_count++;
            p_aruco_direct_mean.x += (-msg.poses[4*i+swarm_ID-5].x);
            p_aruco_direct_mean.y += (-msg.poses[4*i+swarm_ID-5].y);
            p_aruco_direct_mean.z += (-msg.poses[4*i+swarm_ID-5].z);
        }
        ////求直接观测结果的平均值
        if(aruco_direct_count>1){//一个值也无所谓平均了
            p_aruco_direct_mean.x /= aruco_direct_count;
            p_aruco_direct_mean.y /= aruco_direct_count;
            p_aruco_direct_mean.z /= aruco_direct_count;

        }
        ////一次间接观察到的结果
        int aruco_1hop_count = 0;
        geometry_msgs::Point p_aruco_1hop_mean;
        for(int j=1;j<=4;j++){
            //找一个点，既不是swarm_ID，也不是i无人机
            if(j==swarm_ID || j==i) continue;
            //存在从swarm_ID到j到i的一条观测路径，或者反之
            if(msg.poses[4*swarm_ID+j-5].x!=0 && msg.poses[4*j+i-5].x!=0){
                aruco_1hop_count++;
                p_aruco_1hop_mean.x += msg.poses[4*swarm_ID+j-5].x + msg.poses[4*j+i-5].x;
                p_aruco_1hop_mean.y += msg.poses[4*swarm_ID+j-5].y + msg.poses[4*j+i-5].y;
                p_aruco_1hop_mean.z += msg.poses[4*swarm_ID+j-5].z + msg.poses[4*j+i-5].z;
            }
            //被观察到
            if(msg.poses[4*i+j-5].x!=0 && msg.poses[4*j+swarm_ID-5].x!=0){
                aruco_1hop_count++;
                p_aruco_1hop_mean.x += (-msg.poses[4*i+j-5].x - msg.poses[4*j+swarm_ID-5].x);
                p_aruco_1hop_mean.y += (-msg.poses[4*i+j-5].y - msg.poses[4*j+swarm_ID-5].y);
                p_aruco_1hop_mean.z += (-msg.poses[4*i+j-5].z - msg.poses[4*j+swarm_ID-5].z);
            }
        }
        ////求一次间接观测结果的平均值
        if(aruco_1hop_count>1){//一个值也无所谓平均了
            p_aruco_1hop_mean.x /= aruco_1hop_count;
            p_aruco_1hop_mean.y /= aruco_1hop_count;
            p_aruco_1hop_mean.z /= aruco_1hop_count;

        }
        ////二次间接观察到的结果
        int aruco_2hop_count = 0;
        geometry_msgs::Point p_aruco_2hop_mean;
        for(int j=1;j<=4;j++) {
            //找一个点，既不是swarm_ID，也不是i无人机
            if(j==swarm_ID || j==i) continue;
            for(int k=1;k<=4;k++){
                if(k==j || k==i || k==swarm_ID) continue;
                //存在从swarm_ID到j到k到i的一条观测路径，或者反之
                if(msg.poses[4*swarm_ID+j-5].x!=0 && msg.poses[4*j+k-5].x!=0 && msg.poses[4*k+i-5].x!=0){
                    aruco_2hop_count++;
                    p_aruco_2hop_mean.x += msg.poses[4*swarm_ID+j-5].x + msg.poses[4*j+k-5].x + msg.poses[4*k+i-5].x;
                    p_aruco_2hop_mean.y += msg.poses[4*swarm_ID+j-5].y + msg.poses[4*j+k-5].y + msg.poses[4*k+i-5].y;
                    p_aruco_2hop_mean.z += msg.poses[4*swarm_ID+j-5].z + msg.poses[4*j+k-5].z + msg.poses[4*k+i-5].z;
                }
                //被观察到
                if(msg.poses[4*i+k-5].x!=0 && msg.poses[4*k+j-5].x!=0 && msg.poses[4*j+swarm_ID-5].x!=0){
                    aruco_2hop_count++;
                    p_aruco_2hop_mean.x += (-msg.poses[4*i+k-5].x - msg.poses[4*k+j-5].x - msg.poses[4*j+swarm_ID-5].x);
                    p_aruco_2hop_mean.y += (-msg.poses[4*i+k-5].y - msg.poses[4*k+j-5].y - msg.poses[4*j+swarm_ID-5].y);
                    p_aruco_2hop_mean.z += (-msg.poses[4*i+k-5].z - msg.poses[4*k+j-5].z - msg.poses[4*j+swarm_ID-5].z);
                }

            }
        }
        ////求二次间接观测结果的平均值
        if(aruco_2hop_count>1){//一个值也无所谓平均了
            p_aruco_2hop_mean.x /= aruco_2hop_count;
            p_aruco_2hop_mean.y /= aruco_2hop_count;
            p_aruco_2hop_mean.z /= aruco_2hop_count;

        }
        //第三项，预测结果
        geometry_msgs::Point p_predict;
        int pred_count = 0;
        //if(swarm_pre_vel[i-1].x!=0 && swarm_pre_vel[swarm_ID-1].x!=0){
        {
            //同时存在速度值
            pred_count = 1;
            ros::Duration delta_t = ros::Time::now()-t_last_cb;
            double dt=delta_t.toSec();//收到信息的时间间隔
            if(dt>1.0/10) dt=1.0/10;
            double k_lowpass = 0.3;//低通滤波的系数
            p_predict.x = swarm_pred.poses[i-1].x*(1-k_lowpass)+k_lowpass*(swarm_pre_pos[i-1].x+(swarm_pre_vel[i-1].x-swarm_pre_vel[swarm_ID-1].x)*dt);
            p_predict.y = swarm_pred.poses[i-1].y*(1-k_lowpass)+k_lowpass*(swarm_pre_pos[i-1].y+(swarm_pre_vel[i-1].y-swarm_pre_vel[swarm_ID-1].y)*dt);
            p_predict.z = swarm_pred.poses[i-1].z*(1-k_lowpass)+k_lowpass*(swarm_pre_pos[i-1].z+(swarm_pre_vel[i-1].z-swarm_pre_vel[swarm_ID-1].z)*dt);

        }
        //进行数据融合
        bool could_fusion = false;//判断当前数据是否足以完成融合，能的话更新融合结果，不能的话保持原样
        if(pred_count==0 && aruco_direct_count==0 && aruco_1hop_count==0 && aruco_2hop_count==0 && t265_count==0){
            //说明三个来源的数据都没有，无法进行融合工作,当前位置直接继承上一个位置
            swarm_cur_pos[i-1].x = swarm_pre_pos[i-1].x;
            swarm_cur_pos[i-1].y = swarm_pre_pos[i-1].y;
            swarm_cur_pos[i-1].z = swarm_pre_pos[i-1].z;
        }
        else{
            //可以融合
            //记录各个分项的值，用于记录csv
            swarm_vio.poses[i-1] = p_t265;
            swarm_pred.poses[i-1] = p_predict;
            swarm_aruco2.poses[i-1] = p_aruco_2hop_mean;
            swarm_aruco1.poses[i-1] = p_aruco_1hop_mean;
            swarm_aruco0.poses[i-1] = p_aruco_direct_mean;
            //查看哪些数据可以融合，并给与权重
//            w_t265 = 50*t265_count;
//            w_a1 = 2*aruco_direct_count;
//            w_a1hop = 1*aruco_1hop_count;
//            w_a2hop = 1*aruco_2hop_count;
//            w_pred = 50*pred_count;
//            double w = w_t265 + w_a1 + w_a1hop + w_a2hop + w_pred;
//            geometry_msgs::Point p_fusion;
//            p_fusion.x = (p_t265.x*w_t265 + p_aruco_direct_mean.x*w_a1 + p_aruco_1hop_mean.x*w_a1hop + p_aruco_2hop_mean.x*w_a2hop + p_predict.x*w_pred)/w;
//            p_fusion.y = (p_t265.y*w_t265 + p_aruco_direct_mean.y*w_a1 + p_aruco_1hop_mean.y*w_a1hop + p_aruco_2hop_mean.y*w_a2hop + p_predict.y*w_pred)/w;
//            p_fusion.z = (p_t265.z*w_t265 + p_aruco_direct_mean.z*w_a1 + p_aruco_1hop_mean.z*w_a1hop + p_aruco_2hop_mean.z*w_a2hop + p_predict.z*w_pred)/w;

            //使用ceres求解器求解最优解
            //定义需要求解的变量，初值选择上一时刻的位置，以求更快收敛
            geometry_msgs::Point p_fusion;
            p_fusion.x = swarm_pre_pos[i-1].x;
            p_fusion.y = swarm_pre_pos[i-1].y;
            p_fusion.z = swarm_pre_pos[i-1].z;
//            p_fusion.x = 1;
//            p_fusion.y = 1;
//            p_fusion.z = 1;
            Problem pb;
            if(t265_count!=0){//存在测量值，加入优化函数
                CostFunction* ct =
                        new AutoDiffCostFunction<PointResidual,3,1,1,1>(
                                new PointResidual(p_t265.x,p_t265.y,p_t265.z,w_t265));
                pb.AddResidualBlock(ct, NULL, &p_fusion.x,&p_fusion.y,&p_fusion.z);
            }
            if(aruco_direct_count!=0){//存在测量值，加入优化函数
                CostFunction* ct =
                        new AutoDiffCostFunction<PointResidual,3,1,1,1>(
                                new PointResidual(p_aruco_direct_mean.x,p_aruco_direct_mean.y,p_aruco_direct_mean.z,w_a1));
                pb.AddResidualBlock(ct, NULL, &p_fusion.x,&p_fusion.y,&p_fusion.z);
            }
            if(aruco_1hop_count!=0){//存在测量值，加入优化函数
                CostFunction* ct =
                        new AutoDiffCostFunction<PointResidual,3,1,1,1>(
                                new PointResidual(p_aruco_1hop_mean.x,p_aruco_1hop_mean.y,p_aruco_1hop_mean.z,w_a1hop));
                pb.AddResidualBlock(ct, NULL, &p_fusion.x,&p_fusion.y,&p_fusion.z);
            }
            if(aruco_2hop_count!=0){//存在测量值，加入优化函数
                CostFunction* ct =
                        new AutoDiffCostFunction<PointResidual,3,1,1,1>(
                                new PointResidual(p_aruco_2hop_mean.x,p_aruco_2hop_mean.y,p_aruco_2hop_mean.z,w_a2hop));
                pb.AddResidualBlock(ct, NULL, &p_fusion.x,&p_fusion.y,&p_fusion.z);
            }
            if(pred_count!=0){//存在测量值，加入优化函数
                CostFunction* ct =
                        new AutoDiffCostFunction<PointResidual,3,1,1,1>(
                                new PointResidual(p_predict.x,p_predict.y,p_predict.z,w_pred));
                pb.AddResidualBlock(ct, NULL, &p_fusion.x,&p_fusion.y,&p_fusion.z);
            }
            if(uwb_dis.distance[i-1]>0 ){//距离为正
                double tmp = prev_uwb_dis.distance[i-1];//用于对比
                prev_uwb_dis.distance[i-1] = uwb_dis.distance[i-1];//将有效的值存入上一时刻的uwb值,用于滤波
                if(abs(uwb_dis.distance[i-1]-tmp)<0.4){//且没有跳变
                    double k_lowpass = 0.3;//低通滤波的系数
                    uwb_dis.distance[i-1] = uwb_dis.distance[i-1]*(1-k_lowpass)+prev_uwb_dis.distance[i-1]*k_lowpass;//滤波后的值
                    CostFunction* ct =
                            new AutoDiffCostFunction<UWBResidual,1,1,1,1>(
                                    new UWBResidual(uwb_dis.distance[i-1], w_uwb));
                    pb.AddResidualBlock(ct, NULL, &p_fusion.x,&p_fusion.y,&p_fusion.z);
                }
                else{
                    //uwb的值不可信,改为-2，存入csv
                    uwb_dis.distance[i-1] = -2;
                }

            }

            Solver::Options options;
            options.max_num_iterations = 25;
            options.linear_solver_type = ceres::DENSE_QR;
            Solver::Summary summary;
            Solve(options, &pb, &summary);
            //std::cout << summary.BriefReport() << "\n";
            //更新上一时刻的值
            swarm_pre_pos[i-1].x = swarm_cur_pos[i-1].x = p_fusion.x;
            swarm_pre_pos[i-1].y = swarm_cur_pos[i-1].y = p_fusion.y;
            swarm_pre_pos[i-1].z = swarm_cur_pos[i-1].z = p_fusion.z;

        }


    }

    //存储上一时刻的速度
    for(int i=0; i<4; i++){
        swarm_pre_vel[i].x = msg.vel[i].x;
        swarm_pre_vel[i].y = msg.vel[i].y;
        swarm_pre_vel[i].z = msg.vel[i].z;
    }

    //所有另外三架飞机全部完成了相对位置估计，发布估计结果
    nlink_parser::SwarmPosStamped fusion_result;
    for(int i=0; i<4; i++){
        if(i==swarm_ID-1) continue;
        //其他无人机相对于自己的位置
        fusion_result.poses[i].x = swarm_cur_pos[i].x;
        fusion_result.poses[i].y = swarm_cur_pos[i].y;
        fusion_result.poses[i].z = swarm_cur_pos[i].z;
    }
    //发布无人机自己的位置
    fusion_result.poses[swarm_ID-1].x = msg.poses[5*swarm_ID-5].x;
    fusion_result.poses[swarm_ID-1].y = msg.poses[5*swarm_ID-5].y;
    fusion_result.poses[swarm_ID-1].z = msg.poses[5*swarm_ID-5].z;
    //加上时间戳
    fusion_result.header.frame_id = "world";
    fusion_result.header.stamp = msg.header.stamp;
    fusion_result.header.seq = swarm_fusion_pos_seq_count++;
    swarm_fusion_pos_pub.publish(fusion_result);
    //存入文件
    if(save_csv){
        fstream fs;
        fs.open(path_csv, std::fstream::in | std::fstream::out | std::fstream::app);
        if(fs.is_open()){
            fs <<  fusion_result.header.stamp.sec<<","<<fusion_result.header.stamp.nsec<<","<<
                   fusion_result.poses[0].x<<","<< fusion_result.poses[0].y<<","<< fusion_result.poses[0].z<<","<<
                   fusion_result.poses[1].x<<","<< fusion_result.poses[1].y<<","<< fusion_result.poses[1].z<<","<<
                   fusion_result.poses[2].x<<","<< fusion_result.poses[2].y<<","<< fusion_result.poses[2].z<<","<<
                   fusion_result.poses[3].x<<","<< fusion_result.poses[3].y<<","<< fusion_result.poses[3].z<<","<<
                   swarm_pred.poses[0].x<<","<< swarm_pred.poses[0].y<<","<< swarm_pred.poses[0].z<<","<<
                   swarm_pred.poses[1].x<<","<< swarm_pred.poses[1].y<<","<< swarm_pred.poses[1].z<<","<<
                   swarm_pred.poses[2].x<<","<< swarm_pred.poses[2].y<<","<< swarm_pred.poses[2].z<<","<<
                   swarm_pred.poses[3].x<<","<< swarm_pred.poses[3].y<<","<< swarm_pred.poses[3].z<<","<<
                   swarm_vio.poses[0].x<<","<< swarm_vio.poses[0].y<<","<< swarm_vio.poses[0].z<<","<<
                   swarm_vio.poses[1].x<<","<< swarm_vio.poses[1].y<<","<< swarm_vio.poses[1].z<<","<<
                   swarm_vio.poses[2].x<<","<< swarm_vio.poses[2].y<<","<< swarm_vio.poses[2].z<<","<<
                   swarm_vio.poses[3].x<<","<< swarm_vio.poses[3].y<<","<< swarm_vio.poses[3].z<<","<<
                   swarm_aruco0.poses[0].x<<","<< swarm_aruco0.poses[0].y<<","<< swarm_aruco0.poses[0].z<<","<<
                   swarm_aruco0.poses[1].x<<","<< swarm_aruco0.poses[1].y<<","<< swarm_aruco0.poses[1].z<<","<<
                   swarm_aruco0.poses[2].x<<","<< swarm_aruco0.poses[2].y<<","<< swarm_aruco0.poses[2].z<<","<<
                   swarm_aruco0.poses[3].x<<","<< swarm_aruco0.poses[3].y<<","<< swarm_aruco0.poses[3].z<<","<<
                   swarm_aruco1.poses[0].x<<","<< swarm_aruco1.poses[0].y<<","<< swarm_aruco1.poses[0].z<<","<<
                   swarm_aruco1.poses[1].x<<","<< swarm_aruco1.poses[1].y<<","<< swarm_aruco1.poses[1].z<<","<<
                   swarm_aruco1.poses[2].x<<","<< swarm_aruco1.poses[2].y<<","<< swarm_aruco1.poses[2].z<<","<<
                   swarm_aruco1.poses[3].x<<","<< swarm_aruco1.poses[3].y<<","<< swarm_aruco1.poses[3].z<<","<<
                   swarm_aruco2.poses[0].x<<","<< swarm_aruco2.poses[0].y<<","<< swarm_aruco2.poses[0].z<<","<<
                   swarm_aruco2.poses[1].x<<","<< swarm_aruco2.poses[1].y<<","<< swarm_aruco2.poses[1].z<<","<<
                   swarm_aruco2.poses[2].x<<","<< swarm_aruco2.poses[2].y<<","<< swarm_aruco2.poses[2].z<<","<<
                   swarm_aruco2.poses[3].x<<","<< swarm_aruco2.poses[3].y<<","<< swarm_aruco2.poses[3].z<<","<<
                   uwb_dis.distance[0]<<","<<uwb_dis.distance[1]<<","<<uwb_dis.distance[2]<<","<<uwb_dis.distance[3]<<endl;
            }
        }
        else{
            ROS_ERROR_STREAM("fail to open csv file");
        }


    //计算程序用时
    ros::Duration t_cost = ros::Time::now() - t_begin;
    ROS_INFO_STREAM_THROTTLE(1, "fusion time cost: "<<t_cost.toSec()*1000<<" ms");
    t_last_cb = ros::Time::now();//回调时间，用于计算两个估计的时间差，计算预测值


}

void loadSwarmInitPos(ros::NodeHandle &nh) {
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
    //以swarm_ID无人机为基准，即以自身为基准，进行相对位置换算
    for (int i = 0; i < 4; i++) {
        if((swarm_ID-1)==i) continue;
        swarm_init_pos[i].x = swarm_init_pos[i].x - swarm_init_pos[swarm_ID-1].x;
        swarm_init_pos[i].y = swarm_init_pos[i].y - swarm_init_pos[swarm_ID-1].y;
        swarm_init_pos[i].z = swarm_init_pos[i].z - swarm_init_pos[swarm_ID-1].z;
    }
    swarm_init_pos[swarm_ID-1].x = 0;
    swarm_init_pos[swarm_ID-1].y = 0;
    swarm_init_pos[swarm_ID-1].z = 0;
    for (int i = 0; i < 4; i++) {
        //给初始估计赋值
        swarm_pre_pos[i].x = swarm_init_pos[i].x;
        swarm_pre_pos[i].y = swarm_init_pos[i].y;
        swarm_pre_pos[i].z = swarm_init_pos[i].z;
        ROS_INFO_STREAM("swarm_"<< i+1 << ": "<< swarm_init_pos[i].x<<", "<<swarm_init_pos[i].y<<", "<<swarm_init_pos[i].z);
    }
}

void writecsvheader(){
    //获取系统时间
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
//    std::puts(buffer);
    path_csv = path_csv+buffer+"-uav"+std::to_string(swarm_ID)+"-swarm_state_estimate.csv";
//    std::cout<<path_csv<<endl;
    fstream fs;
    fs.open(path_csv, ios::out);
    if(fs.is_open()){
        fs << "t_sec,t_nsec";
        for(int m=1;m<=4;m++){
            fs << ",est_x"+std::to_string(swarm_ID)+std::to_string(m)
               << ",est_y"+std::to_string(swarm_ID)+std::to_string(m)
               << ",est_z"+std::to_string(swarm_ID)+std::to_string(m);
            }
        for(int m=1;m<=4;m++){
            fs << ",pred_x"+std::to_string(swarm_ID)+std::to_string(m)
               << ",pred_y"+std::to_string(swarm_ID)+std::to_string(m)
               << ",pred_z"+std::to_string(swarm_ID)+std::to_string(m);
        }
        for(int m=1;m<=4;m++){
            fs << ",t265_x"+std::to_string(swarm_ID)+std::to_string(m)
               << ",t265_y"+std::to_string(swarm_ID)+std::to_string(m)
               << ",t265_z"+std::to_string(swarm_ID)+std::to_string(m);
        }
        for(int m=1;m<=4;m++){
            fs << ",aruco0_x"+std::to_string(swarm_ID)+std::to_string(m)
               << ",aruco0_y"+std::to_string(swarm_ID)+std::to_string(m)
               << ",aruco0_z"+std::to_string(swarm_ID)+std::to_string(m);
        }
        for(int m=1;m<=4;m++){
            fs << ",aruco1_x"+std::to_string(swarm_ID)+std::to_string(m)
               << ",aruco1_y"+std::to_string(swarm_ID)+std::to_string(m)
               << ",aruco1_z"+std::to_string(swarm_ID)+std::to_string(m);
        }
        for(int m=1;m<=4;m++){
            fs << ",aruco2_x"+std::to_string(swarm_ID)+std::to_string(m)
               << ",aruco2_y"+std::to_string(swarm_ID)+std::to_string(m)
               << ",aruco2_z"+std::to_string(swarm_ID)+std::to_string(m);
        }
        for(int m=1;m<=4;m++){
            fs << ",uwb_dis"+std::to_string(swarm_ID)+std::to_string(m);
        }
        fs << endl;
    }
    else{
        ROS_ERROR_STREAM("fail to open csv file");
    }

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "swarm_state_est_node");
    ros::NodeHandle nh;
    //init param
    readParam<float>(nh, "w_t265",w_t265);
    readParam<float>(nh, "w_a1",w_a1);
    readParam<float>(nh, "w_a1hop",w_a1hop);
    readParam<float>(nh, "w_a2hop",w_a2hop);
    readParam<float>(nh, "w_pred",w_pred);
    readParam<float>(nh, "w_uwb",w_uwb);
    readParam<int>(nh, "swarm_ID",swarm_ID);
    readParam<bool>(nh, "save_csv",save_csv);
    readParam<string>(nh, "path_csv",path_csv);
    std::string uav_name = "/uav"+to_string(swarm_ID);
    loadSwarmInitPos(nh);
    if(save_csv){
        writecsvheader();
    }
    t_last_cb = ros::Time::now();
    //sub & pub
    ros::Subscriber swarm_info_sub = nh.subscribe(uav_name+"/uwb_recv_detected_aruco_pose", 1, swarm_info_cb);
    ros::Subscriber uwb_dis_sub = nh.subscribe(uav_name+"/uwb_dis_stamped_smoothed", 1, uwb_dis_cb);
    swarm_fusion_pos_pub = nh.advertise<nlink_parser::SwarmPosStamped>(uav_name+"/swarm_fusion_pos", 1);

//    message_filters::Subscriber<nlink_parser::SwarmInfoStamped> swarm_info_sub(nh, uav_name+"/uwb_recv_detected_aruco_pose", 1);
//    message_filters::Subscriber<nlink_parser::UWBDisStamped> uwb_dis_sub(nh, uav_name+"/uwb_dis_stamped", 1);
//
//    typedef sync_policies::ApproximateTime<nlink_parser::SwarmInfoStamped, nlink_parser::UWBDisStamped> MySyncPolicy;
//    // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
//    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), swarm_info_sub, uwb_dis_sub);
//    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

    return 0;
}
