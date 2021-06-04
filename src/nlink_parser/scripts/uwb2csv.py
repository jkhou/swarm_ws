#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
from scipy.signal import savgol_filter, filtfilt, butter
import rospy
import csv
import message_filters
from geometry_msgs.msg import PoseStamped
from nlink_parser.msg import UWBDisStamped
import time
now = time.strftime("%Y%m%d-%H-%M-%S",time.localtime(time.time()))
SAVE_PATH="/home/zph/rosbag/"
filename = SAVE_PATH+"uwb_data"+now+".csv"
# for uwb dis filter

data_l = 101
sub_count = 0
dis12 = np.zeros(data_l)
dis13 = np.zeros(data_l)
dis14 = np.zeros(data_l)

dis21 = np.zeros(data_l)
dis23 = np.zeros(data_l)
dis24 = np.zeros(data_l)

dis31 = np.zeros(data_l)
dis32 = np.zeros(data_l)
dis34 = np.zeros(data_l)

dis41 = np.zeros(data_l)
dis42 = np.zeros(data_l)
dis43 = np.zeros(data_l)


def synccallback(
                    uwbdis1,uwbdis2,uwbdis3,uwbdis4
                    ):
    part1 = [  uwbdis1.header.stamp,
            uwbdis1.distance[0], uwbdis1.distance[1], uwbdis1.distance[2], uwbdis1.distance[3], 
            uwbdis2.distance[0], uwbdis2.distance[1], uwbdis2.distance[2], uwbdis2.distance[3], 
            uwbdis3.distance[0], uwbdis3.distance[1], uwbdis3.distance[2], uwbdis3.distance[3], 
            uwbdis4.distance[0], uwbdis4.distance[1], uwbdis4.distance[2], uwbdis4.distance[3]
    ] 
    global dis12
    global dis13
    global dis14

    global dis21
    global dis23
    global dis24

    global dis31
    global dis32
    global dis34

    global dis41
    global dis42
    global dis43

    gate = 1
    if(uwbdis1.distance[1]>0 and abs(uwbdis1.distance[1]-dis12[-1])<gate or dis12[-1]==0):
        dis12 = np.append(dis12, uwbdis1.distance[1])
        dis12 = np.delete(dis12, 0)
    if(uwbdis1.distance[2]>0 and abs(uwbdis1.distance[2]-dis13[-1])<gate or dis13[-1]==0):
        dis13 = np.append(dis13, uwbdis1.distance[2])
        dis13 = np.delete(dis13, 0)
    if(uwbdis1.distance[3]>0 and abs(uwbdis1.distance[3]-dis14[-1])<gate or dis14[-1]==0):
        dis14 = np.append(dis14, uwbdis1.distance[3])
        dis14 = np.delete(dis14, 0)

    if(uwbdis2.distance[0]>0 and abs(uwbdis2.distance[0]-dis21[-1])<gate or dis21[-1]==0):
        dis21 = np.append(dis21, uwbdis2.distance[0])
        dis21 = np.delete(dis21, 0)
    if(uwbdis2.distance[2]>0 and abs(uwbdis2.distance[2]-dis23[-1])<gate or dis23[-1]==0):
        dis23 = np.append(dis23, uwbdis2.distance[2])
        dis23 = np.delete(dis23, 0)
    if(uwbdis2.distance[3]>0 and abs(uwbdis2.distance[3]-dis24[-1])<gate or dis24[-1]==0):
        dis24 = np.append(dis24, uwbdis2.distance[3])
        dis24 = np.delete(dis24, 0)

    if(uwbdis3.distance[0]>0 and abs(uwbdis3.distance[0]-dis31[-1])<gate or dis31[-1]==0):
        dis31 = np.append(dis31, uwbdis3.distance[0])
        dis31 = np.delete(dis31, 0)
    if(uwbdis3.distance[1]>0 and abs(uwbdis3.distance[1]-dis32[-1])<gate or dis32[-1]==0):
        dis32 = np.append(dis32, uwbdis3.distance[1])
        dis32 = np.delete(dis32, 0)
    if(uwbdis3.distance[3]>0 and abs(uwbdis3.distance[3]-dis34[-1])<gate or dis34[-1]==0):
        dis34 = np.append(dis34, uwbdis3.distance[3])
        dis34 = np.delete(dis34, 0)

    if(uwbdis4.distance[0]>0 and abs(uwbdis4.distance[0]-dis41[-1])<gate or dis41[-1]==0):
        dis41 = np.append(dis41, uwbdis4.distance[0])
        dis41 = np.delete(dis41, 0)
    if(uwbdis4.distance[1]>0 and abs(uwbdis4.distance[1]-dis42[-1])<gate or dis42[-1]==0):
        dis42 = np.append(dis42, uwbdis4.distance[1])
        dis42 = np.delete(dis42, 0)
    if(uwbdis4.distance[2]>0 and abs(uwbdis4.distance[2]-dis43[-1])<gate or dis43[-1]==0):
        dis43 = np.append(dis43, uwbdis4.distance[2])
        dis43 = np.delete(dis43, 0)

    #sg filter
    order = 3
    window = 33
    smooth12 = savgol_filter(dis12, window, order)
    smooth13 = savgol_filter(dis13, window, order)
    smooth14 = savgol_filter(dis14, window, order)

    smooth21 = savgol_filter(dis21, window, order)
    smooth23 = savgol_filter(dis23, window, order)
    smooth24 = savgol_filter(dis24, window, order)

    smooth31 = savgol_filter(dis31, window, order)
    smooth32 = savgol_filter(dis32, window, order)
    smooth34 = savgol_filter(dis34, window, order)

    smooth41 = savgol_filter(dis41, window, order)
    smooth42 = savgol_filter(dis42, window, order)
    smooth43 = savgol_filter(dis43, window, order)
    
    #msg pub
    uwbdis1s = UWBDisStamped()
    uwbdis2s = UWBDisStamped()
    uwbdis3s = UWBDisStamped()
    uwbdis4s = UWBDisStamped()

    uwbdis1s.header = uwbdis1.header
    uwbdis2s.header = uwbdis2.header
    uwbdis3s.header = uwbdis3.header
    uwbdis3s.header = uwbdis4.header

    uwbdis1s.distance[1] = smooth12[-1]
    uwbdis1s.distance[2] = smooth13[-1]
    uwbdis1s.distance[3] = smooth14[-1]

    uwbdis2s.distance[0] = smooth21[-1]
    uwbdis2s.distance[2] = smooth23[-1]
    uwbdis2s.distance[3] = smooth24[-1]  

    uwbdis3s.distance[0] = smooth31[-1]
    uwbdis3s.distance[1] = smooth32[-1]
    uwbdis3s.distance[3] = smooth34[-1]
    
    uwbdis4s.distance[0] = smooth41[-1]
    uwbdis4s.distance[1] = smooth42[-1]
    uwbdis4s.distance[2] = smooth43[-1]

    ## decide wether publish
    global sub_count
    sub_count += 1
    global data_l
    if(sub_count>data_l):
        smooth1_pub.publish(uwbdis1s)
        smooth2_pub.publish(uwbdis2s)
        smooth3_pub.publish(uwbdis3s)
        smooth4_pub.publish(uwbdis4s)
    

    part2 = [
            uwbdis1s.distance[0], uwbdis1s.distance[1], uwbdis1s.distance[2], uwbdis1s.distance[3], 
            uwbdis2s.distance[0], uwbdis2s.distance[1], uwbdis2s.distance[2], uwbdis2s.distance[3], 
            uwbdis3s.distance[0], uwbdis3s.distance[1], uwbdis3s.distance[2], uwbdis3s.distance[3], 
            uwbdis4s.distance[0], uwbdis4s.distance[1], uwbdis4s.distance[2], uwbdis4s.distance[3]
    ]   
  
    with open(filename, 'a') as csvfile:
        uav1_writer = csv.writer(csvfile, lineterminator='\n')
        uav1_writer.writerow(part1+part2)
    return

def writehead():
    with open(filename, 'a') as csvfile:
        uav1_writer = csv.writer(csvfile, lineterminator='\n')
        uav1_writer.writerow([
                            'uwb_t_sec',
                            'uwbdis11', 'uwbdis12', 'uwbdis13', 'uwbdis14', 
                            'uwbdis21', 'uwbdis22', 'uwbdis23', 'uwbdis24', 
                            'uwbdis31', 'uwbdis32', 'uwbdis33', 'uwbdis34', 
                            'uwbdis41', 'uwbdis42', 'uwbdis43', 'uwbdis44',
                            'uwbdis11s', 'uwbdis12s', 'uwbdis13s', 'uwbdis14s', 
                            'uwbdis21s', 'uwbdis22s', 'uwbdis23s', 'uwbdis24s', 
                            'uwbdis31s', 'uwbdis32s', 'uwbdis33s', 'uwbdis34s', 
                            'uwbdis41s', 'uwbdis42s', 'uwbdis43s', 'uwbdis44s'
                            ])

if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("uwb2csv")
    writehead()


    uwb_dis_sub1 = message_filters.Subscriber("/uav1/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub2 = message_filters.Subscriber("/uav2/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub3 = message_filters.Subscriber("/uav3/uwb_dis_stamped", UWBDisStamped)
    uwb_dis_sub4 = message_filters.Subscriber("/uav4/uwb_dis_stamped", UWBDisStamped)
    
    msgsync = message_filters.ApproximateTimeSynchronizer([
                                                    uwb_dis_sub1, uwb_dis_sub2, uwb_dis_sub3, uwb_dis_sub4 
                                                    ], 
                                                    50, 0.1)
    msgsync.registerCallback(synccallback)

    # pub topic 
    global smooth1_pub
    smooth1_pub = rospy.Publisher("/uav1/uwb_dis_stamped_smoothed", UWBDisStamped, queue_size=1)
    global smooth2_pub
    smooth2_pub = rospy.Publisher("/uav2/uwb_dis_stamped_smoothed", UWBDisStamped, queue_size=1)
    global smooth3_pub
    smooth3_pub = rospy.Publisher("/uav3/uwb_dis_stamped_smoothed", UWBDisStamped, queue_size=1)
    global smooth4_pub
    smooth4_pub = rospy.Publisher("/uav4/uwb_dis_stamped_smoothed", UWBDisStamped, queue_size=1)

    rospy.spin()