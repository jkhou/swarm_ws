#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import csv
import message_filters
from geometry_msgs.msg import PoseStamped
from visualization_msgs.msg import MarkerArray, Marker
from nlink_parser.msg import SwarmPos
from nlink_parser.msg import LinktrackNodeframe3
from nav_msgs.msg import Odometry
import time
now = time.strftime("%Y%m%d-%H-%M-%S",time.localtime(time.time()))
SAVE_PATH="/home/zph/rosbag/"
filename = SAVE_PATH+"uav_odom_data"+now+".csv"

def synccallback(odom1,odom2,odom3,odom4):
    with open(filename, 'a') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow([
            odom1.header.stamp,

            odom1.pose.pose.position.x, odom1.pose.pose.position.y, odom1.pose.pose.position.z,
            odom2.pose.pose.position.x, odom2.pose.pose.position.y, odom2.pose.pose.position.z,
            odom3.pose.pose.position.x, odom3.pose.pose.position.y, odom3.pose.pose.position.z,
            odom4.pose.pose.position.x, odom4.pose.pose.position.y, odom4.pose.pose.position.z,

            odom1.twist.twist.linear.x, odom1.twist.twist.linear.y, odom1.twist.twist.linear.z,
            odom2.twist.twist.linear.x, odom2.twist.twist.linear.y, odom2.twist.twist.linear.z,
            odom3.twist.twist.linear.x, odom3.twist.twist.linear.y, odom3.twist.twist.linear.z,
            odom4.twist.twist.linear.x, odom4.twist.twist.linear.y, odom4.twist.twist.linear.z

            ])
    return
    

def writehead():
    with open(filename, 'a') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow([
                            't_odom',
                            'mav1x', 'mav1y', 'mav1z', 
                            'mav2x', 'mav2y', 'mav2z', 
                            'mav3x', 'mav3y', 'mav3z', 
                            'mav4x', 'mav4y', 'mav4z', 
                            'mav_vel1x', 'mav_vel1y', 'mav_vel1z',
                            'mav_vel2x', 'mav_vel2y', 'mav_vel2z',
                            'mav_vel3x', 'mav_vel3y', 'mav_vel3z',
                            'mav_vel4x', 'mav_vel4y', 'mav_vel4z'
                            
                           
        ])

if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("vio2csv")
    writehead()
    # sub topic
    odom_sub1 = message_filters.Subscriber("/uav1/mavros/local_position/odom",Odometry)
    odom_sub2 = message_filters.Subscriber("/uav2/mavros/local_position/odom",Odometry)
    odom_sub3 = message_filters.Subscriber("/uav3/mavros/local_position/odom",Odometry)
    odom_sub4 = message_filters.Subscriber("/uav4/mavros/local_position/odom",Odometry)
   
    msgsync = message_filters.ApproximateTimeSynchronizer([
                                                    odom_sub1, odom_sub2, odom_sub3, odom_sub4
                                                   
                                                    ], 
                                                    50, 0.2)
    msgsync.registerCallback(synccallback)
    rospy.spin()