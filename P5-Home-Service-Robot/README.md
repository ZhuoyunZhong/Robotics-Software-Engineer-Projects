# Home Service Robot

[![](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](http://www.udacity.com/robotics)

## Result Demonstration 

### Video demonstration

 [![Video demonstration](./demonstration/P5.gif)](https://youtu.be/-6iFxDoOUwM)

## Overview

This project integrates mapping, localization and path planning to navigate the robot and implement a pick&drop task. The robot is spawned in an apartment, whose map was built using slam technique previously. The robot then uses laser scan to localize itself in the environment. Two goal poses are given for picking and dropping a certain object. The robot plans the path and navigate to the desired poses one after another in order to achieve the pick&drop task.

## Run Instruction
#### Platform:

Ubuntu 18 + ROS melodic

#### Prerequisite

Install ROS packages: [gmapping](http://wiki.ros.org/gmapping) and [turtlebot3](http://wiki.ros.org/turtlebot3?distro=melodic).

To build the scripts

```
$ cd home/catkin_ws
$ catkin_make
```

#### Run

Launch the home service robot

```
$ cd catkin_ws/src/P5-Home-Service-Robot/scripts
$ chmod +x home_service.sh
$ ./home_service.sh
```

## Project Detail

#### Mapping

```
$ cd catkin_ws/src/P5-Home-Service-Robot/scripts
$ chmod +x test_slam.sh
$ ./test_slam.sh
```

The apartment's map is built with `gmapping` using slam technique. The robot was manually driven around the apartment with turtlebot3 keyboard controller `turtlebot3_teleop`. The resulting map `apartment.pgm` and `apartment.yaml` files are saved in `turtlebot3_world/worlds`.

#### Localization and Navigation

```
$ cd catkin_ws/src/P5-Home-Service-Robot/scripts
$ chmod +x test_navigation.sh
$ ./test_navigation.sh
```

Loaded the map built from slam module, the robot then can use Monte Carlo Localization package `amcl` to localize itself in the apartment. `amcl` also provides the ability to navigate the robot to a certain desired pose with the help of `move_base`, which plans the path and controls the robot wheels' velocity.

#### Home Service

```
$ cd catkin_ws/src/P5-Home-Service-Robot/scripts
$ chmod +x add_marker.sh pick_objects.sh
$ ./add_marker.sh
$ ./pick_objects.sh
```

The final goal is to navigate robot to two desired location in order to achieve pick and drop task. The `add_marker.sh` can create a fake object box, once the robot picks it up, it will disappear and will appear when the robot reaches the drop goal. `pick_objects` sent desired pose to `amcl` so that the navigation module can plan the path and navigate the robot to the goals.

## Directory Structure

```
# Official ROS packages
|
amcl                                # localization and navigation
├── ...
slam_gmapping               		# slam                
├── gmapping
├── ...
turtlebot3                     		# turtlebot 3
├── turtlebot_teleop                # keyboard_teleop file
├── turtlebot_description           # turtlebot3 urdf
├── ...
|
|
P5-Home-Service-Robot     		    # This package
├── scripts                   		# shell scripts files
|   ├── home_service.sh
|   ├── add_marker.sh
|   ├── pick_objects.sh
|   ├── test_slam.sh
|   ├── test_navigation.sh
├── turtlebot3_command              # home service code
│   ├── launch                      # launch file
│   |   ├── turtlebot3_command.launch
|   ├── src
│   |   ├── pick_objects.cpp
│   |   ├── add_markers.cpp
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
├── ├── p5.gif
└── README.md                  		# Readme file                                          
```

