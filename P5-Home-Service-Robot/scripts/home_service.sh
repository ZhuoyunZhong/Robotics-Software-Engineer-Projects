#!/bin/sh

xterm  -e  "roslaunch turtlebot3_world turtlebot3_world.launch" &
sleep 5

xterm -e "roslaunch turtlebot3_world amcl.launch" &
sleep 5

xterm  -e  "roslaunch turtlebot3_command turtlebot3_command.launch" 