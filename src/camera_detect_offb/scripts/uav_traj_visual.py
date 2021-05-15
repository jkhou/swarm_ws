#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from nav_msgs.msg import Path
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped,Point
from visualization_msgs.msg import Marker
from mavros_msgs.msg import State

# 定义全局变量
path = Path()#rviz中无人机的飞行轨迹
uav_model = Marker()# rviz中表示无人机模型的marker
uav_model.header.frame_id = "map"
uav_model.ns = "uav"
uav_model.id = 0
uav_model.type = Marker().ARROW
uav_model.action = Marker().ADD
uav_model.scale.x = 0.5
uav_model.scale.y = 0.2
uav_model.scale.z = 0.2
uav_model.color.a = 1.0
uav_model.color.r = 0.0
uav_model.color.g = 0.0
uav_model.color.b = 1.0

# 根据无人机的状态改变rviz中模型的颜色
def uavState_cb(cur_state):
    # change color according to uav state
    # print(cur_state)
    if cur_state.mode == "OFFBOARD":
        uav_model.color.r = 1.0
        uav_model.color.g = 0.0
        uav_model.color.b = 0.0
    elif cur_state.mode == "POSCTL":
        uav_model.color.r = 0.0
        uav_model.color.g = 1.0
        uav_model.color.b = 0.0
    else:
        uav_model.color.r = 0.0
        uav_model.color.g = 0.0
        uav_model.color.b = 1.0
    uav_model_pub.publish(uav_model)



# transfer UAV odom data to path data for viusualization in rviz
def odom_cb(data):
    global path
    path.header = data.header
    pose = PoseStamped()
    pose.header = data.header
    pose.pose = data.pose.pose
    ## 判断上一个点与当前点的距离
    global prev_pose
    delt_x = pose.pose.position.x-prev_pose.pose.position.x
    delt_y = pose.pose.position.y-prev_pose.pose.position.y
    delt_z = pose.pose.position.z-prev_pose.pose.position.z
    # avoid too dense points
    min_dis = 0.01
    if(abs(delt_x)>min_dis or abs(delt_y)>min_dis or abs(delt_z)>min_dis):
        prev_pose = pose
        path.poses.append(pose)
        path_pub.publish(path)
    # update uav pose
    global uav_model
    uav_model.header = data.header
    uav_model.pose = data.pose.pose
    uav_model_pub.publish(uav_model)


# ros basic settings
rospy.init_node('uav_traj_visual_node')

## 存储无人机上一时刻位置，用于和当前位置比较
prev_pose = PoseStamped()
prev_pose.pose.position.x = 0
prev_pose.pose.position.y = 0
prev_pose.pose.position.z = 0

## 订阅和发布的消息
odom_sub = rospy.Subscriber('/mavros/local_position/odom', Odometry, odom_cb)
uav_state_sub = rospy.Subscriber('/mavros/state', State, uavState_cb)
path_pub = rospy.Publisher('uav/path', Path, queue_size=10)
uav_model_pub = rospy.Publisher('uav/model', Marker, queue_size=1)


if __name__ == '__main__':
    rospy.spin()