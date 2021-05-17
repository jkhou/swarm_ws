#!/bin/bash
source ~/swarm_ws/devel/setup.zsh
roslaunch camera_detect_offb swarm_all_nodes.launch swarm_ID:=2 & sleep 1

cd ~/swarm_ws/src/camera_detect_offb/scripts/
python3 object_detection_uav1.py


