#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
from scipy.signal import savgol_filter, filtfilt, butter
import rospy
from geometry_msgs.msg import PoseStamped,TwistStamped
import time
x = np.zeros(101)
y = np.zeros(101)
z = np.zeros(101)
# vel_smoothed = TwistStamped()

def smooth_vel_cb(msg):
    time_start = time.time()
    vel_smoothed = msg
    global x
    global y
    global z
    x = np.append(x, msg.twist.linear.x)
    y = np.append(y, msg.twist.linear.y)
    z = np.append(z, msg.twist.linear.z)
    x = np.delete(x, 0)
    y = np.delete(y, 0)
    z = np.delete(z, 0)
    #sg filter
    smooth_x = savgol_filter(x, 15, 3)
    smooth_y = savgol_filter(y, 15, 3)
    smooth_z = savgol_filter(z, 15, 3)

    #Filtfilt
    # b, a = butter(3, 0.042)
    # smooth_x = filtfilt(b, a, x)
    # smooth_y = filtfilt(b, a, y)
    # smooth_z = filtfilt(b, a, z)
    
    vel_smoothed.twist.linear.x = smooth_x[-1]
    vel_smoothed.twist.linear.y = smooth_y[-1]
    vel_smoothed.twist.linear.z = smooth_z[-1]
    smooth_vel_pub.publish(vel_smoothed)
    time_end = time.time()
    # print('Time cost = %fs' % (time_end - time_start))
    


if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("mav_smooth")
    swarm_ID = 0
    swarm_ID = rospy.get_param("~swarm_ID")
    uav_name = '/uav'+str(swarm_ID)
    
    # sub topic
    rospy.Subscriber(uav_name+"/mavros/local_position/velocity_local",TwistStamped,smooth_vel_cb)
 
    # pub topic 
    global smooth_vel_pub
    smooth_vel_pub = rospy.Publisher(uav_name+"/mavros/local_position/velocity_local_smoothed",TwistStamped, queue_size=1)

    rospy.spin()