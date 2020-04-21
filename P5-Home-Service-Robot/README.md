# Home Service Robot

[![](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](http://www.udacity.com/robotics)

## Result Demonstration 

### Video demonstration

 [![Video demonstration](./demonstration/P5.gif)](https://youtu.be/?)

## Overview

This project is to 

Platform:
Ubuntu 18 + ROS melodic

## Run Instruction
Prerequisite
Install these packages:
[Gmapping](http://wiki.ros.org/gmapping), [turtlebot3](http://wiki.ros.org/turtlebot3?distro=melodic)

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
|
|
P5-Home-Service-Robot     		    # This package
├── scripts                   		# shell scripts files
|   ├── launch.sh
├── pick_objects                    # pick_objects C++ node
|   ├── src/pick_objects.cpp
│   ├── CMakeLists.txt
│   ├── package.xml
├── add_markers                     # add_marker C++ node
│   ├── src/add_markers.cpp
│   ├── CMakeLists.txt
│   ├── package.xml
├── turtlebot3_world                # turtlebot3 world
│   ├── rvizConfig                  # Rviz config
│   |   ├── turtlebot.rviz
│   ├── worlds                      # World urdf
│   |   ├── apartment.world
│   ├── launch                      # World launch
│   |   ├── turtlebot3_world.launch
│   ├── CMakeLists.txt
│   ├── package.xml
├── demonstration             		# Demonstrate file for README 
├── ├── p3.gif
└── README.md                  		# Readme file                                          
```

