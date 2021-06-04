#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import csv
import message_filters
from geometry_msgs.msg import PoseStamped
from visualization_msgs.msg import MarkerArray, Marker
from nlink_parser.msg import SwarmInfoStamped
from nlink_parser.msg import UWBDisStamped
from nav_msgs.msg import Odometry
import time
now = time.strftime("%Y%m%d-%H-%M-%S",time.localtime(time.time()))
SAVE_PATH="/home/zph/rosbag/"
filename = SAVE_PATH+"data"+now+".csv"

def synccallback(   aruco1,
                    # aruco2,aruco3,aruco4,
                    uwbdis1,uwbdis2,uwbdis3,uwbdis4,
                    # vicon1,vicon2,vicon3,vicon4
                    ):
    l1=[]
    for i in range(16):
        l1 = l1 + [aruco1.poses[i].x, aruco1.poses[i].y, aruco1.poses[i].z]


    l2 = []
    for i in range(4):
        l2 = l2 + [aruco1.vel[i].x, aruco1.vel[i].y, aruco1.vel[i].z]

    # l3=[vicon1.pose.position.x,vicon1.pose.position.y,vicon1.pose.position.z,
    #     vicon2.pose.position.x,vicon2.pose.position.y,vicon2.pose.position.z,
    #     vicon3.pose.position.x,vicon3.pose.position.y,vicon3.pose.position.z,
    #     vicon4.pose.position.x,vicon4.pose.position.y,vicon4.pose.position.z
    # ]

    l5 = [  uwbdis1.distance[0], uwbdis1.distance[1], uwbdis1.distance[2], uwbdis1.distance[3], 
            uwbdis2.distance[0], uwbdis2.distance[1], uwbdis2.distance[2], uwbdis2.distance[3], 
            uwbdis3.distance[0], uwbdis3.distance[1], uwbdis3.distance[2], uwbdis3.distance[3], 
            uwbdis4.distance[0], uwbdis4.distance[1], uwbdis4.distance[2], uwbdis4.distance[3], 
    ]   
  
    with open(filename, 'a') as csvfile:
        uav1_writer = csv.writer(csvfile, lineterminator='\n')
        uav1_writer.writerow(l1+l2+l5)
    return

def writehead():
    with open(filename, 'a') as csvfile:
        uav1_writer = csv.writer(csvfile, lineterminator='\n')
        uav1_writer.writerow(['vis11x', 'vis11y', 'vis11z', 
                            'vis12x', 'vis12y', 'vis12z', 
                            'vis13x', 'vis13y', 'vis13z', 
                            'vis14x', 'vis14y', 'vis14z', 
                            'vis21x', 'vis21y', 'vis21z', 
                            'vis22x', 'vis22y', 'vis22z', 
                            'vis23x', 'vis23y', 'vis23z', 
                            'vis24x', 'vis24y', 'vis24z',
                            'vis31x', 'vis31y', 'vis31z', 
                            'vis32x', 'vis32y', 'vis32z', 
                            'vis33x', 'vis33y', 'vis33z', 
                            'vis34x', 'vis34y', 'vis34z',
                            'vis41x', 'vis41y', 'vis41z', 
                            'vis42x', 'vis42y', 'vis42z', 
                            'vis43x', 'vis43y', 'vis43z', 
                            'vis44x', 'vis44y', 'vis44z',
                            'vel1x', 'vel1y', 'vel1z',
                            'vel2x', 'vel2y', 'vel2z',
                            'vel3x', 'vel3y', 'vel3z',
                            'vel4x', 'vel4y', 'vel4z',
                            # 'vicon1x','vicon1y','vicon1z',
                            # 'vicon2x','vicon2y','vicon2z',
                            # 'vicon3x','vicon3y','vicon3z',
                            # 'vicon4x','vicon4y','vicon4z',
                            'uwbdis11', 'uwbdis12', 'uwbdis13', 'uwbdis14', 
                            'uwbdis21', 'uwbdis22', 'uwbdis23', 'uwbdis24', 
                            'uwbdis31', 'uwbdis32', 'uwbdis33', 'uwbdis34', 
                            'uwbdis41', 'uwbdis42', 'uwbdis43', 'uwbdis44', 
                            ])

if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("init_pos_est")
    writehead()
    # sub topic
    aruco_sub1 = message_filters.Subscriber("/uav1/uwb_recv_detected_aruco_pose",SwarmInfoStamped)
    # aruco_sub2 = message_filters.Subscriber("/uav2/uwb_recv_detected_aruco_pose",SwarmInfoStamped)
    # aruco_sub3 = message_filters.Subscriber("/uav3/uwb_recv_detected_aruco_pose",SwarmInfoStamped)
    # aruco_sub4 = message_filters.Subscriber("/uav4/uwb_recv_detected_aruco_pose",SwarmInfoStamped)

    uwb_dis_sub1 = message_filters.Subscriber("/uav1/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub2 = message_filters.Subscriber("/uav2/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub3 = message_filters.Subscriber("/uav3/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub4 = message_filters.Subscriber("/uav4/uwb_dis_stamped", UWBDisStamped)

    # vicon_sub1 = message_filters.Subscriber("/UAV1/viconros/mocap/pos", PoseStamped)
    # vicon_sub2 = message_filters.Subscriber("/UAV2/viconros/mocap/pos", PoseStamped)
    # vicon_sub3 = message_filters.Subscriber("/UAV3/viconros/mocap/pos", PoseStamped)
    # vicon_sub4 = message_filters.Subscriber("/UAV4/viconros/mocap/pos", PoseStamped)

    
    msgsync = message_filters.ApproximateTimeSynchronizer([ aruco_sub1,       
                                                            # aruco_sub2,       aruco_sub3,       aruco_sub4,
                                                            uwb_dis_sub1,     uwb_dis_sub2,     uwb_dis_sub3,     uwb_dis_sub4,
                                                            # vicon_sub1,       vicon_sub2,       vicon_sub3,       vicon_sub4 
                                                            ], 
                                                            50, 0.1)
    msgsync.registerCallback(synccallback)
    rospy.spin()