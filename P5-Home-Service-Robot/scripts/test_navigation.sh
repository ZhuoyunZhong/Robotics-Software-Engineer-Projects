#!/bin/sh

xterm  -e  "roslaunch turtlebot3_world turtlebot3_world.launch" &
sleep 3

xterm  -e  "roslaunch turtlebot3_world amcl.launch"  &
