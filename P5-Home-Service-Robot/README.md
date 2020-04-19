# Home Service Robot

[![](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](http://www.udacity.com/robotics)

## Result Demonstration 

### Video demonstration

 [![Video demonstration](./demonstration/P5.gif)](https://youtu.be/?)

## Overview

This project is to 

## Run Instruction

To build the scripts

```
$ cd home/catkin_ws
$ catkin_make
```

Launch the world file and scripts in Gazebo

```
$ roslaunch mcl_robot world.launch
$ roslaunch mcl_robot amcl.launch
```

## Directory Structure

```
# Official ROS packages
|
slam_gmapping               		# gmapping_demo.launch file                 
├── gmapping
├── ...
turtlebot                     		# keyboard_teleop.launch file
├── turtlebot_teleop
├── ...
turtlebot_interactions         		# view_navigation.launch file      
├── turtlebot_rviz_launchers
├── ...
turtlebot_simulator           		# turtlebot_world.launch file 
├── turtlebot_gazebo
└── ...
|
|
P5-Home-Service-Robot     		    # This package
├── map                             # map files
|   ├── ...
├── scripts                   		# shell scripts files
|   ├── ...
├── rvizConfig                      # rviz configuration files
|   ├── ...
├── pick_objects                    # pick_objects C++ node
|   ├── src/pick_objects.cpp
│   ├── ...
├── add_markers                     # add_marker C++ node
│   ├── src/add_markers.cpp
│   ├── ...
├── demonstration             		# Demonstrate file for README 
├── ├── p3.gif
└── README.md                  		# Readme file                                          
```

