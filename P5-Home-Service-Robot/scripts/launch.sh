#!/bin/sh

xterm  -e  " gazebo " &
sleep 3

xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 3

xterm  -e  " rosrun rviz rviz" 