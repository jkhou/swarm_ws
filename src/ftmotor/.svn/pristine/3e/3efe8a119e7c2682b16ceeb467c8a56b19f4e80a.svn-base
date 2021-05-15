#!/usr/bin/env python
#coding:utf-8
import rospy
from nav_msgs.msg import Odometry
from std_msgs.msg import String
from _Flow.msg import Flow
from tf.transformations import euler_from_quaternion, quaternion_from_euler
from serial import Serial
from math import atan2,asin,sin,cos,pi
from struct import *
import time
import numpy as np

# author： Sundongxiao Zhangpeihan
# 读取T265 驱动数据并以串口方法发布
# 需要设置偏置大小
# 使用的物体坐标系均为机体坐标系
# 当T265镜头向前，数据接口向右时，相机坐标系为前左上，飞控机头一致时对应飞机坐标系为

ser=Serial("/dev/ttyS0",19200,timeout=0.5)

# 突变跳跃的检测阈值
DISTANCE_SCALE_F = 0.1 # 10cm

# SCALE大小，飞机解析时设置同样数值
SCALE_F = 10000.0

#FRD坐标系，右手法则末状态减初状态角度
#如 右方向为正，斜前向下（俯角）30°旋转到正视前方
#末状态正视前方减初状态斜前方30°，右手一转方向相反，大拇指向左，代入-30
FIXED_T265_ROLL = 0 #不旋转
FIXED_T265_PITCH = 0 # -30,-45  -pi/6,-pi/4 
FIXED_T265_YAW = 0 #不旋转

# 飞机坐标系下面的偏置
OFFSET_X = 0.012
OFFSET_Y = 0
OFFSET_Z = 0
# 打印当前状态
print_status = 1

# 抵消偏置后的位置
send_pos = np.array([0.0,0.0,0.0])

# 检测突变后位置（差值累加）
current_pos = np.array([0.0,0.0,0.0])
current_angle = np.array([0.0,0.0,0.0])
current_pos_raw = np.array([0.0,0.0,0.0])
last_pos_raw = np.array([0.0,0.0,0.0])

# 计算ab向量之间的距离
def getLength(a,b):
    return ((a[0]-b[0])**2+(a[1]-b[1])**2+(a[2]-b[2])**2)**0.5

# 自动使用T265 的旋转角度自主补偿偏置引起的位置误差
# 其中使用的offset设置来自机体坐标系
# 使用的旋转角度坐标系也来自飞机坐标系
# 最后send_pos 是修正后的数据
# current_pos xyz, current_angle roll,pitch,yaw
def compensate_offset(current_pos,current_angle):
    offset = np.array([OFFSET_X,OFFSET_Y,OFFSET_Z,1])
    t265_T = np.zeros((4,4))
    t265_T[0][0] = cos(current_angle[1])*cos(current_angle[2])
    t265_T[0][1] = -cos(current_angle[1])*sin(current_angle[2])
    t265_T[0][2] = sin(current_angle[1])
    t265_T[1][0] = cos(current_angle[0])*sin(current_angle[2])+sin(current_angle[0])*sin(current_angle[1])*cos(current_angle[2])
    t265_T[1][1] = cos(current_angle[0])*cos(current_angle[2])-sin(current_angle[0])*sin(current_angle[1])*sin(current_angle[2])
    t265_T[1][2] = -sin(current_angle[0])*cos(current_angle[1])
    t265_T[2][0] = sin(current_angle[0])*sin(current_angle[2])-cos(current_angle[0])*sin(current_angle[1])*cos(current_angle[2])
    t265_T[2][1] = sin(current_angle[0])*cos(current_angle[2])+cos(current_angle[0])*sin(current_angle[1])*sin(current_angle[2])
    t265_T[2][2] = cos(current_angle[0])*cos(current_angle[1])
    t265_T[0][3] = -OFFSET_X
    t265_T[1][3] = -OFFSET_Y
    t265_T[2][3] = -OFFSET_Z
    t265_T[3][3] = 1
    send_pos = current_pos-t265_T.dot(offset)[0:3]
    return send_pos

# 发送int 数据   
# 发送之前对检测过跳变的数据进行修正，之后发送修正的数据
def send_intdata(current_pos,current_angle,Quaternion_num,length,flag,current_pos_raw,last_pos_raw):
    # 修正函数
    send_pos = compensate_offset(current_pos,current_angle)
    # print log 
    if print_status:
        rospy.loginfo(
        '------------------------------------\n'
        'distance : \t %2.4f jerk_status : %s\n'
        '[RAW DATA] X:\t%2.4f Y:\t%2.4f Z:\t%2.4f\n'
        '[LAST DATA] X_1:\t%2.4f Y_1:\t%2.4f Z_1:\t%2.4f\n'
        '[SEND DATA] X:\t%2.4f Y_1:\t%2.4f Z_1:\t%2.4f\n'
        'R:\t%2.4f P:\t%2.4f Y:\t%2.4f\n' 
        'W:\t%2.4f X:\t%2.4f Y:\t%2.4f Z:\t%2.4f'
        %(
        (float)(length),
        flag,
        (float)(current_pos_raw[0]),
        (float)(current_pos_raw[1]),
        (float)(current_pos_raw[2]),
        (float)(last_pos_raw[0]),
        (float)(last_pos_raw[1]),
        (float)(last_pos_raw[2]),
        (float)(current_pos[0]),
        (float)(current_pos[1]),
        (float)(current_pos[2]),
        (float)(current_angle[0]),
        (float)(current_angle[1]),
        (float)(current_angle[2]),
        (float)(Quaternion_num[0]),
        (float)(Quaternion_num[1]),
        (float)(Quaternion_num[2]),
        (float)(Quaternion_num[3])
        ))

    _roll = int(SCALE_F*current_angle[0])
    _pitch = int(SCALE_F*current_angle[1])
    _yaw = int(SCALE_F*current_angle[2])
    _x = int(SCALE_F*send_pos[0])
    _y = int(SCALE_F*send_pos[1])
    _z = int(SCALE_F*send_pos[2])
    
    msg = Flow()
    msg.pos = 1.0*send_pos
    msg.theta = 1.0*current_angle
    pub.publish(msg)

    data = pack('>2b7ib',-2,34,_x,_y,_z,_roll,_pitch,_yaw,(_x+_y+_z+_roll+_pitch+_yaw),20)
    ser.write(data)

# 对于T265安装角度的旋转矩阵
def rotate_raw_pos(x,y,z):
    raw_data = np.array([x,y,z])
    theta = np.array([FIXED_T265_ROLL,FIXED_T265_PITCH,FIXED_T265_YAW])
    # R_pitch = np.array([[cos(theta),0,sin(theta)],[0,1,0],[-sin(theta),0,cos(theta)]])
    # R_pitch.dot(raw_data[1])
    R = np.zeros((3,3))
    R[0][0] = cos(theta[1])*cos(theta[2])
    R[0][1] = -cos(theta[1])*sin(theta[2])
    R[0][2] = sin(theta[1])
    R[1][0] = cos(theta[0])*sin(theta[2])+sin(theta[0])*sin(theta[1])*cos(theta[2])
    R[1][1] = cos(theta[0])*cos(theta[2])-sin(theta[0])*sin(theta[1])*sin(theta[2])
    R[1][2] = -sin(theta[0])*cos(theta[1])
    R[2][0] = sin(theta[0])*sin(theta[2])-cos(theta[0])*sin(theta[1])*cos(theta[2])
    R[2][1] = sin(theta[0])*cos(theta[2])+cos(theta[0])*sin(theta[1])*sin(theta[2])
    R[2][2] = cos(theta[0])*cos(theta[1])
    x,y,z = R.dot(raw_data)
    return x,y,z

def callback(odom):
    global hz
    global current_pos
    global last_pos_raw
    global pub

    if hz == 4:
        hz = 0
        # print(odom)
        # origin Quaternion data
        x1 = odom.pose.pose.orientation.x
        y1 = odom.pose.pose.orientation.y
        z1 = odom.pose.pose.orientation.z
        w1 = odom.pose.pose.orientation.w
        Quaternion_num = np.array([w1,x1,y1,z1])

        # calculate Eular angle
            # alpha = int(atan2(2*(w1*x1+y1*z1),1-2*(x1*x1+y1*y1))*SCALE_F)
            # beta = int(asin(2*(w1*y1-x1*z1))*SCALE_F)
            # garma = int(atan2(2*(w1*z1+x1*y1),1-2*(z1*z1+y1*y1))*SCALE_F)
        # 直接更正坐标系
        (roll, pitch, yaw) = euler_from_quaternion ([x1,y1,z1,w1])
        pitch = -1.0 * pitch
        yaw = -1.0 * yaw
        x = odom.pose.pose.position.x
        y = -1.0*odom.pose.pose.position.y
        z = -1.0*odom.pose.pose.position.z

        # 对t265安装pitch角度旋转变化
        x,y,z = rotate_raw_pos(x,y,z)

        current_angle[0] = roll
        current_angle[1] = pitch
        current_angle[2] = yaw
        current_pos_raw[0] = x
        current_pos_raw[1] = y
        current_pos_raw[2] = z

        length = getLength(current_pos_raw,last_pos_raw)

        # detect jerk
        if abs(length) <= DISTANCE_SCALE_F:  
            flag = 'NO'
            # send data
            current_pos = 1.0*current_pos + current_pos_raw - last_pos_raw
            send_intdata(current_pos,current_angle,Quaternion_num,length,flag,current_pos_raw,last_pos_raw)
            
        else:
            flag = 'YES'
            # strategy 1 do not use new pos ，just use last pos
            send_intdata(current_pos,current_angle,Quaternion_num,length,flag,current_pos_raw,last_pos_raw)
            
            # TODO：strategy 2 use flow pos

        # 复制一份，而不是指针
        last_pos_raw = 1.0*current_pos_raw
        # _time = time.time()
        # print('%02X %02X %04X %04X %04X %04X %04X %04X %04X %02X'%(-2,34,x,y,z,alpha,beta,garma,x+y+z+alpha+beta+garma,20))
        # global pub
        # pub.publish(data)
    else:
        hz = hz + 1
        return

def start():
    # starts the node
    rospy.init_node('Realsense2Serial')
    # some global variable

    if ser.isOpen():
        rospy.loginfo("open success")
    else:
        rospy.loginfo("open failed")    
        
    global hz # 200/5 hz = 4
    hz = 0
    global pub
    global x
    x = 0
    #publish position data
    pub = rospy.Publisher('/PositionData', Flow, queue_size=10)
     # subscribed to realsense inputs on topic "odom"
    rospy.Subscriber("/camera/odom/sample", Odometry, callback)

    rospy.loginfo("start to send position data to serial")
    rospy.spin()


if __name__ == '__main__':
    start()