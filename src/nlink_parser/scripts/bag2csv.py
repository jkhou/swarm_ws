#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import csv
import message_filters
from geometry_msgs.msg import PoseStamped
from visualization_msgs.msg import MarkerArray, Marker
from nlink_parser.msg import SwarmPos
from nlink_parser.msg import UWBDisStamped
from nav_msgs.msg import Odometry
import time
now = time.strftime("%Y%m%d-%H-%M-%S",time.localtime(time.time()))
SAVE_PATH="/home/zph/rosbag/"
filename = SAVE_PATH+"data"+now+".csv"

def synccallback(   aruco1,aruco2,aruco3,aruco4,
                    locpos1,locpos2,locpos3,locpos4,
                    vispos1,vispos2,vispos3,vispos4,
                    odom1,odom2,odom3,odom4,
                    uwbdis1,uwbdis2,uwbdis3,uwbdis4
                    ):
    l1=[]
    for i in range(16):
        l1 = l1 + [aruco1.swarm_pos[i].x, aruco1.swarm_pos[i].y, aruco1.swarm_pos[i].z]
    l2 = [  
            locpos1.pose.position.x, locpos1.pose.position.y, locpos1.pose.position.z,
            locpos2.pose.position.x, locpos2.pose.position.y, locpos2.pose.position.z,
            locpos3.pose.position.x, locpos3.pose.position.y, locpos3.pose.position.z,
            locpos4.pose.position.x, locpos4.pose.position.y, locpos4.pose.position.z,
        ]
    l3 = [
            vispos1.pose.position.x, vispos1.pose.position.y, vispos1.pose.position.z,
            vispos2.pose.position.x, vispos2.pose.position.y, vispos2.pose.position.z,
            vispos3.pose.position.x, vispos3.pose.position.y, vispos3.pose.position.z,
            vispos4.pose.position.x, vispos4.pose.position.y, vispos4.pose.position.z,
        ]
    l4 = [
        odom1.twist.twist.linear.x, odom1.twist.twist.linear.y, odom1.twist.twist.linear.z, 
        odom2.twist.twist.linear.x, odom2.twist.twist.linear.y, odom2.twist.twist.linear.z, 
        odom3.twist.twist.linear.x, odom3.twist.twist.linear.y, odom3.twist.twist.linear.z, 
        odom4.twist.twist.linear.x, odom4.twist.twist.linear.y, odom4.twist.twist.linear.z, 
    ]
    l5 = [  uwbdis1.distance[0], uwbdis1.distance[1], uwbdis1.distance[2], uwbdis1.distance[3], 
            uwbdis2.distance[0], uwbdis2.distance[1], uwbdis2.distance[2], uwbdis2.distance[3], 
            uwbdis3.distance[0], uwbdis3.distance[1], uwbdis3.distance[2], uwbdis3.distance[3], 
            uwbdis4.distance[0], uwbdis4.distance[1], uwbdis4.distance[2], uwbdis4.distance[3], 
    ]   
  
    with open(filename, 'a') as csvfile:
        uav1_writer = csv.writer(csvfile, lineterminator='\n')
        uav1_writer.writerow(l1+l2+l3+l4+l5)
    return

def writehead():
    with open(filename, 'a') as csvfile:
        uav1_writer = csv.writer(csvfile, lineterminator='\n')
        uav1_writer.writerow(['1-1x', '1-1y', '1-1z', 
                            '1-2x', '1-2y', '1-2z', 
                            '1-3x', '1-3y', '1-3z', 
                            '1-4x', '1-4y', '1-4z', 
                            '2-1x', '2-1y', '2-1z', 
                            '2-2x', '2-2y', '2-2z', 
                            '2-3x', '2-3y', '2-3z', 
                            '2-4x', '2-4y', '2-4z',
                            '3-1x', '3-1y', '3-1z', 
                            '3-2x', '3-2y', '3-2z', 
                            '3-3x', '3-3y', '3-3z', 
                            '3-4x', '3-4y', '3-4z',
                            '4-1x', '4-1y', '4-1z', 
                            '4-2x', '4-2y', '4-2z', 
                            '4-3x', '4-3y', '4-3z', 
                            '4-4x', '4-4y', '4-4z',
                            'locpos-x1', 'locpos-y1', 'locpos-z1',
                            'locpos-x2', 'locpos-y2', 'locpos-z2',
                            'locpos-x3', 'locpos-y3', 'locpos-z3',
                            'locpos-x4', 'locpos-y4', 'locpos-z4',
                            'vispos-x1', 'vispos-y1', 'vispos-z1',
                            'vispos-x2', 'vispos-y2', 'vispos-z2',
                            'vispos-x3', 'vispos-y3', 'vispos-z3',
                            'vispos-x4', 'vispos-y4', 'vispos-z4',
                            'odom-vel-x1', 'dom-vel-y1', 'odom-vel-z1',
                            'odom-vel-x2', 'dom-vel-y2', 'odom-vel-z2',
                            'odom-vel-x3', 'dom-vel-y3', 'odom-vel-z3',
                            'odom-vel-x4', 'dom-vel-y4', 'odom-vel-z4',
                            'uwbdis1-1', 'uwbdis1-2', 'uwbdis1-3', 'uwbdis1-4', 
                            'uwbdis2-1', 'uwbdis2-2', 'uwbdis2-3', 'uwbdis2-4', 
                            'uwbdis3-1', 'uwbdis3-2', 'uwbdis3-3', 'uwbdis3-4', 
                            'uwbdis4-1', 'uwbdis4-2', 'uwbdis4-3', 'uwbdis4-4', 
                            ])

if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("init_pos_est")
    writehead()
    # sub topic
    aruco_sub1 = message_filters.Subscriber("/uav1/uwb_recv_detected_aruco_pose",SwarmPos)
    aruco_sub2 = message_filters.Subscriber("/uav2/uwb_recv_detected_aruco_pose",SwarmPos)
    aruco_sub3 = message_filters.Subscriber("/uav3/uwb_recv_detected_aruco_pose",SwarmPos)
    aruco_sub4 = message_filters.Subscriber("/uav4/uwb_recv_detected_aruco_pose",SwarmPos)
    # message_filters.Cache(aruco_sub1, 100, allow_headerless=True)
    # message_filters.Cache(aruco_sub2, 100, allow_headerless=True)
    # message_filters.Cache(aruco_sub3, 100, allow_headerless=True)
    # message_filters.Cache(aruco_sub4, 100, allow_headerless=True)

    mav_loc_pos_sub1 = message_filters.Subscriber("/uav1/mavros/local_position/pose", PoseStamped)
    mav_loc_pos_sub2 = message_filters.Subscriber("/uav2/mavros/local_position/pose", PoseStamped)
    mav_loc_pos_sub3 = message_filters.Subscriber("/uav3/mavros/local_position/pose", PoseStamped)
    mav_loc_pos_sub4 = message_filters.Subscriber("/uav4/mavros/local_position/pose", PoseStamped)
    # message_filters.Cache(mav_loc_pos_sub1, 100, allow_headerless=True)
    # message_filters.Cache(mav_loc_pos_sub2, 100, allow_headerless=True)
    # message_filters.Cache(mav_loc_pos_sub3, 100, allow_headerless=True)
    # message_filters.Cache(mav_loc_pos_sub4, 100, allow_headerless=True)

    mav_vis_pos_sub1 = message_filters.Subscriber("/uav1/mavros/vision_pose/pose", PoseStamped)
    mav_vis_pos_sub2 = message_filters.Subscriber("/uav2/mavros/vision_pose/pose", PoseStamped)
    mav_vis_pos_sub3 = message_filters.Subscriber("/uav3/mavros/vision_pose/pose", PoseStamped)
    mav_vis_pos_sub4 = message_filters.Subscriber("/uav4/mavros/vision_pose/pose", PoseStamped)
    # message_filters.Cache(mav_vis_pos_sub1, 100, allow_headerless=True)
    # message_filters.Cache(mav_vis_pos_sub2, 100, allow_headerless=True)
    # message_filters.Cache(mav_vis_pos_sub3, 100, allow_headerless=True)
    # message_filters.Cache(mav_vis_pos_sub4, 100, allow_headerless=True)

    t265_odom_sub1 = message_filters.Subscriber("/uav1/camera/odom/sample", Odometry)
    t265_odom_sub2 = message_filters.Subscriber("/uav2/camera/odom/sample", Odometry)
    t265_odom_sub3 = message_filters.Subscriber("/uav3/camera/odom/sample", Odometry)
    t265_odom_sub4 = message_filters.Subscriber("/uav4/camera/odom/sample", Odometry)
    # message_filters.Cache(t265_odom_sub1, 100, allow_headerless=True)
    # message_filters.Cache(t265_odom_sub2, 100, allow_headerless=True)
    # message_filters.Cache(t265_odom_sub3, 100, allow_headerless=True)   
    # message_filters.Cache(t265_odom_sub4, 100, allow_headerless=True)

    uwb_dis_sub1 = message_filters.Subscriber("/uav1/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub2 = message_filters.Subscriber("/uav2/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub3 = message_filters.Subscriber("/uav3/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub4 = message_filters.Subscriber("/uav4/uwb_dis_stamped", UWBDisStamped)
    # message_filters.Cache(uwb_dis_sub1, 100, allow_headerless=True)
    # message_filters.Cache(uwb_dis_sub2, 100, allow_headerless=True)
    # message_filters.Cache(uwb_dis_sub3, 100, allow_headerless=True)
    # message_filters.Cache(uwb_dis_sub4, 100, allow_headerless=True)
    
    msgsync = message_filters.ApproximateTimeSynchronizer([aruco_sub1, aruco_sub2,      aruco_sub3,       aruco_sub4,
                                                    mav_loc_pos_sub1, mav_loc_pos_sub2, mav_loc_pos_sub3, mav_loc_pos_sub4,
                                                    mav_vis_pos_sub1, mav_vis_pos_sub2, mav_vis_pos_sub3, mav_vis_pos_sub4,
                                                    t265_odom_sub1,   t265_odom_sub2,   t265_odom_sub3,   t265_odom_sub4,
                                                    uwb_dis_sub1,     uwb_dis_sub2,     uwb_dis_sub3,     uwb_dis_sub4 ], 
                                                    50, 0.1)
    msgsync.registerCallback(synccallback)
    rospy.spin()