#!/bin/bash

source /opt/ros/kinetic/setup.bash
source /home/topup/catkin_ws/devel/setup.bash

roslaunch realsense2_camera rs_t265.launch&
rosrun realsense2_camera T265serial.py&
rosrun px4flow upflow_pub
