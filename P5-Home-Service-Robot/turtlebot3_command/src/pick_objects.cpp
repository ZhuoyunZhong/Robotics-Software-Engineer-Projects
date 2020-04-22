#include "ros/ros.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>
#include <std_msgs/Bool.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
    // Initialize the simple_navigation_goals node
    ros::init(argc, argv, "navigation_goals");
    ros::NodeHandle n;
    ros::Publisher success_pub = n.advertise<std_msgs::Bool>("/reach_position", 1);
    std_msgs::Bool reached;
    reached.data = true;

    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // Wait 5 sec for move_base action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal_pick;
    // set up the frame parameters
    goal_pick.target_pose.header.frame_id = "map";
    goal_pick.target_pose.header.stamp = ros::Time::now();
    // Define a position and orientation for the robot to reach
    goal_pick.target_pose.pose.position.x = -3.0;
    goal_pick.target_pose.pose.position.y = -0.5;
    goal_pick.target_pose.pose.orientation.z = -0.707;
    goal_pick.target_pose.pose.orientation.w = 0.707;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal_pick);
    // Wait an infinite time for the results
    ac.waitForResult();
    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Hooray, the base reached the first goal");
        success_pub.publish(reached);
    }
    else{
        ROS_INFO("The base failed");
    }

    ros::Duration(5.0).sleep();

    move_base_msgs::MoveBaseGoal goal_drop;
    // set up the frame parameters
    goal_drop.target_pose.header.frame_id = "map";
    goal_drop.target_pose.header.stamp = ros::Time::now();
    // Define a position and orientation for the robot to reach
    goal_drop.target_pose.pose.position.x = 4.0;
    goal_drop.target_pose.pose.position.y = 0.0;
    goal_drop.target_pose.pose.orientation.z = 0.707;
    goal_drop.target_pose.pose.orientation.w = 0.707;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal_drop);
    // Wait an infinite time for the results
    ac.waitForResult();
    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Hooray, the base reached the second goal");
        success_pub.publish(reached);
    }
    else{
        ROS_INFO("The base failed");
    }

    return 0;
}
