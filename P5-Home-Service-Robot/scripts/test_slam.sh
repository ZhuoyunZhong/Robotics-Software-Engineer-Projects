#!/bin/sh

xterm  -e  "roslaunch turtlebot3_world turtlebot3_world.launch" &
sleep 3

xterm  -e  "rosrun gmapping slam_gmapping" & 
sleep 3

xterm  -e  "rosrun turtlebot3_teleop turtlebot3_teleop_key" &
