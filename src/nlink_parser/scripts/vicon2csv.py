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
filename = SAVE_PATH+"vicondata"+now+".csv"

def synccallback(vicon1,vicon2,vicon3,vicon4,
                    viconv1,viconv2,viconv3,viconv4
                    # vicona1,vicona2,vicona3,vicona4
                    ):
    with open(filename, 'a') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow([
            vicon1.header.stamp,
            vicon1.pose.position.x, vicon1.pose.position.y, vicon1.pose.position.z,
            vicon2.pose.position.x, vicon2.pose.position.y, vicon2.pose.position.z,
            vicon3.pose.position.x, vicon3.pose.position.y, vicon3.pose.position.z,
            vicon4.pose.position.x, vicon4.pose.position.y, vicon4.pose.position.z,

            viconv1.twist.linear.x, viconv1.twist.linear.y, viconv1.twist.linear.z,
            viconv2.twist.linear.x, viconv2.twist.linear.y, viconv2.twist.linear.z,
            viconv3.twist.linear.x, viconv3.twist.linear.y, viconv3.twist.linear.z,
            viconv4.twist.linear.x, viconv4.twist.linear.y, viconv4.twist.linear.z,

            # vicona1.twist.linear.x, vicona1.twist.linear.y, vicona1.twist.linear.z,
            # vicona2.twist.linear.x, vicona2.twist.linear.y, vicona2.twist.linear.z,
            # vicona3.twist.linear.x, vicona3.twist.linear.y, vicona3.twist.linear.z,
            # vicona4.twist.linear.x, vicona4.twist.linear.y, vicona4.twist.linear.z
            
            ])
    return
    

def writehead():
    with open(filename, 'a') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow([
                            'vicon_t_sec',
                            'vicon1x', 'vicon1y', 'vicon1z', 
                            'vicon2x', 'vicon2y', 'vicon2z',  
                            'vicon3x', 'vicon3y', 'vicon3z',  
                            'vicon4x', 'vicon4y', 'vicon4z', 
                            'viconv1x', 'viconv1y', 'viconv1z', 
                            'viconv2x', 'viconv2y', 'viconv2z',  
                            'viconv3x', 'viconv3y', 'viconv3z',  
                            'viconv4x', 'viconv4y', 'viconv4z'
                            # 'vicona1x', 'vicona1y', 'vicona1z', 
                            # 'vicona2x', 'vicona2y', 'vicona2z',  
                            # 'vicona3x', 'vicona3y', 'vicona3z',  
                            # 'vicona4x', 'vicona4y', 'vicona4z'
        ])

if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("vicon2csv")
    writehead()
    # sub topic
    vicon_sub1 = message_filters.Subscriber("/UAV1/viconros/mocap/pos",PoseStamped)
    vicon_sub2 = message_filters.Subscriber("/UAV2/viconros/mocap/pos",PoseStamped)
    vicon_sub3 = message_filters.Subscriber("/UAV3/viconros/mocap/pos",PoseStamped)
    vicon_sub4 = message_filters.Subscriber("/UAV4/viconros/mocap/pos",PoseStamped)

    vicon_vsub1 = message_filters.Subscriber("/UAV1/viconros/mocap/vel",TwistStamped)
    vicon_vsub2 = message_filters.Subscriber("/UAV2/viconros/mocap/vel",TwistStamped)
    vicon_vsub3 = message_filters.Subscriber("/UAV3/viconros/mocap/vel",TwistStamped)
    vicon_vsub4 = message_filters.Subscriber("/UAV4/viconros/mocap/vel",TwistStamped)

    # vicon_asub1 = message_filters.Subscriber("/UAV1/viconros/mocap/acc",TwistStamped)
    # vicon_asub2 = message_filters.Subscriber("/UAV2/viconros/mocap/acc",TwistStamped)
    # vicon_asub3 = message_filters.Subscriber("/UAV3/viconros/mocap/acc",TwistStamped)
    # vicon_asub4 = message_filters.Subscriber("/UAV4/viconros/mocap/acc",TwistStamped)

    msgsync = message_filters.ApproximateTimeSynchronizer([
                                                    vicon_sub1, vicon_sub2, vicon_sub3, vicon_sub4,
                                                    vicon_vsub1, vicon_vsub2, vicon_vsub3, vicon_vsub4
                                                    #vicon_asub1, vicon_asub2, vicon_asub3, vicon_asub4
                                                    ], 
                                                    50, 0.2)
    msgsync.registerCallback(synccallback)
    rospy.spin()