#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "geometry_msgs/Twist.h"


class ServerAndPublish {
private:
    ros::NodeHandle n_; 
    ros::Publisher joint_pub_;
    ros::ServiceServer service_;

public:
    ServerAndPublish() {
        //Topic to publish
        joint_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

        //Service to provide
        service_ = n_.advertiseService("/ball_chaser/command_robot", &ServerAndPublish::handle_command_request, this);
    }
    ~ServerAndPublish() {}

    // This callback function executes whenever a safe_move service is requested
    bool handle_command_request(ball_chaser::DriveToTarget::Request& req,
        ball_chaser::DriveToTarget::Response& res) {

        ROS_INFO("Command received - lin_x:%1.2f, ang_z:%1.2f", (float)req.linear_x, (float)req.angular_z);

        // Define Type
        geometry_msgs::Twist motor_command;
        // Set wheel velocities, forward [0.5, 0.0]
        motor_command.linear.x = req.linear_x;
        motor_command.angular.z = req.angular_z;
        // Publish angles to drive the robot
        joint_pub_.publish(motor_command);

        // Published message
        return true;
    }
};


int main(int argc, char** argv)
{
    // Initialize the arm_mover node and create a handle to it
    ros::init(argc, argv, "drive_bot");

    //Create an object of class ServerAndPublish that will take care of everything
    ServerAndPublish SAPObject;

    ROS_INFO("Ready to provide command server");

    // Handle ROS communication events
    ros::spin();

    return 0;
}
