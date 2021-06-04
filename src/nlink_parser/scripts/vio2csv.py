#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import csv
import message_filters
from geometry_msgs.msg import PoseStamped,TwistStamped
from visualization_msgs.msg import MarkerArray, Marker
from nlink_parser.msg import SwarmPos
from nlink_parser.msg import LinktrackNodeframe3
from nav_msgs.msg import Odometry
import time
now = time.strftime("%Y%m%d-%H-%M-%S",time.localtime(time.time()))
SAVE_PATH="/home/zph/rosbag/"
filename = SAVE_PATH+"vio_data"+now+".csv"

def synccallback(vio1,vio2,vio3,vio4,viov1,viov2,viov3,viov4):
    with open(filename, 'a') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow([
            vio1.header.stamp,

            vio1.pose.position.x, vio1.pose.position.y, vio1.pose.position.z,
            vio2.pose.position.x, vio2.pose.position.y, vio2.pose.position.z,
            vio3.pose.position.x, vio3.pose.position.y, vio3.pose.position.z,
            vio4.pose.position.x, vio4.pose.position.y, vio4.pose.position.z,

            viov1.twist.linear.x, viov1.twist.linear.y, viov1.twist.linear.z,
            viov2.twist.linear.x, viov2.twist.linear.y, viov2.twist.linear.z,
            viov3.twist.linear.x, viov3.twist.linear.y, viov3.twist.linear.z,
            viov4.twist.linear.x, viov4.twist.linear.y, viov4.twist.linear.z

            ])
    return
    

def writehead():
    with open(filename, 'a') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow([
                            'vio_t_sec',
                            'vio1x', 'vio1y', 'vio1z', 
                            'vio2x', 'vio2y', 'vio2z', 
                            'vio3x', 'vio3y', 'vio3z', 
                            'vio4x', 'vio4y', 'vio4z',
                            'viov1x', 'viov1y', 'viov1z',  
                            'viov2x', 'viov2y', 'viov2z', 
                            'viov3x', 'viov3y', 'viov3z', 
                            'viov4x', 'viov4y', 'viov4z'
                           
        ])

if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("vio2csv")
    writehead()
    # sub topic
    t265_sub1 = message_filters.Subscriber("/uav1/mavros/vision_pose/pose",PoseStamped)
    t265_sub2 = message_filters.Subscriber("/uav2/mavros/vision_pose/pose",PoseStamped)
    t265_sub3 = message_filters.Subscriber("/uav3/mavros/vision_pose/pose",PoseStamped)
    t265_sub4 = message_filters.Subscriber("/uav4/mavros/vision_pose/pose",PoseStamped)

    viov_sub1 = message_filters.Subscriber("/uav1/mavros/local_position/velocity_local_smoothed",TwistStamped)
    viov_sub2 = message_filters.Subscriber("/uav2/mavros/local_position/velocity_local_smoothed",TwistStamped)
    viov_sub3 = message_filters.Subscriber("/uav3/mavros/local_position/velocity_local_smoothed",TwistStamped)
    viov_sub4 = message_filters.Subscriber("/uav4/mavros/local_position/velocity_local_smoothed",TwistStamped)
    


    msgsync = message_filters.ApproximateTimeSynchronizer([
                                                    t265_sub1, t265_sub2, t265_sub3, t265_sub4,
                                                    viov_sub1, viov_sub2, viov_sub3, viov_sub4
                                                
                                                    ], 
                                                    50, 0.2)
    msgsync.registerCallback(synccallback)
    rospy.spin()