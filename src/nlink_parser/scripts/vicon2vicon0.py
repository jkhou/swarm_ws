#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from geometry_msgs.msg import PoseStamped,TwistStamped

firstmsg1 = 0
firstmsg2 = 0
firstmsg3 = 0
firstmsg4 = 0
initpos1 = PoseStamped()
initpos2 = PoseStamped()
initpos3 = PoseStamped()
initpos4 = PoseStamped()

def vicon1pos_cb(msg):
    global firstmsg1
    if(firstmsg1<10):
        firstmsg1 += 1
        global initpos1
        initpos1 = msg
        return
    
    pos = msg
    pos.pose.position.x = pos.pose.position.x - initpos1.pose.position.x
    pos.pose.position.y = pos.pose.position.y - initpos1.pose.position.y
    pos.pose.position.z = pos.pose.position.z - initpos1.pose.position.z
    vicon1pos_pub.publish(pos)

def vicon2pos_cb(msg):
    global firstmsg2
    if(firstmsg2<10):
        firstmsg2 += 1
        global initpos2
        initpos2 = msg
        return
    
    pos = msg
    pos.pose.position.x = pos.pose.position.x - initpos2.pose.position.x
    pos.pose.position.y = pos.pose.position.y - initpos2.pose.position.y
    pos.pose.position.z = pos.pose.position.z - initpos2.pose.position.z
    vicon2pos_pub.publish(pos)

def vicon3pos_cb(msg):
    global firstmsg3
    if(firstmsg3<10):
        firstmsg3 += 1
        global initpos3
        initpos3 = msg
        return
    
    pos = msg
    pos.pose.position.x = pos.pose.position.x - initpos3.pose.position.x
    pos.pose.position.y = pos.pose.position.y - initpos3.pose.position.y
    pos.pose.position.z = pos.pose.position.z - initpos3.pose.position.z
    vicon3pos_pub.publish(pos)

def vicon4pos_cb(msg):
    global firstmsg4
    if(firstmsg4<10):
        firstmsg4 += 1
        global initpos4
        initpos4 = msg
        return
    
    pos = msg
    pos.pose.position.x = pos.pose.position.x - initpos4.pose.position.x
    pos.pose.position.y = pos.pose.position.y - initpos4.pose.position.y
    pos.pose.position.z = pos.pose.position.z - initpos4.pose.position.z
    vicon4pos_pub.publish(pos)





if __name__=="__main__":
    # ros 初始化设置
    rospy.init_node("vicon2vicon0")
    
    # sub topic
    rospy.Subscriber("/UAV1/viconros/mocap/pos",PoseStamped,vicon1pos_cb)
    rospy.Subscriber("/UAV2/viconros/mocap/pos",PoseStamped,vicon2pos_cb)
    rospy.Subscriber("/UAV3/viconros/mocap/pos",PoseStamped,vicon3pos_cb)
    rospy.Subscriber("/UAV4/viconros/mocap/pos",PoseStamped,vicon4pos_cb)
    
    # pub topic 
    global vicon1pos_pub
    global vicon2pos_pub
    global vicon3pos_pub
    global vicon4pos_pub
    vicon1pos_pub = rospy.Publisher("/uav1/viconros/mocap/pos",PoseStamped, queue_size=1)
    vicon2pos_pub = rospy.Publisher("/uav2/viconros/mocap/pos",PoseStamped, queue_size=1)
    vicon3pos_pub = rospy.Publisher("/uav3/viconros/mocap/pos",PoseStamped, queue_size=1)
    vicon4pos_pub = rospy.Publisher("/uav4/viconros/mocap/pos",PoseStamped, queue_size=1)

    rospy.spin()