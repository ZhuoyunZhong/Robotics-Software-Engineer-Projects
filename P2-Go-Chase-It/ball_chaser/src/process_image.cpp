#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


class SubscribeAndClient {
private:
    ros::NodeHandle n_; 
    ros::Subscriber image_sub_;
    ros::ServiceClient client_;

public:
    SubscribeAndClient() {
        //Topic to publish
        image_sub_ = n_.subscribe("/camera/rgb/image_raw", 10, &SubscribeAndClient::process_image_callback, this);

        //Service to provide
        client_ = n_.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    }
    ~SubscribeAndClient() {}

    // This callback function executes whenever a safe_move service is requested
    void process_image_callback(const sensor_msgs::Image img) {
        // White ball color
        int white_pixel = 255;
        // Containers
        float lin_x = 0.0;
        float ang_z = 0.0;
        float ball_pos = 0.0;

        bool white_ball = false;

        // Loop through each pixel in the image and check if its equal to the first one
        for (int i = 0; i < img.height * img.step; i++) {
            ROS_INFO(img.data[i]);
            if (img.data[i] - 255 != 0) {
                white_ball = true;
                break;
            }
        }

        // If the white ball is found
        if (white_ball == true) {
            lin_x = 1.0;
            ang_z = 0.0;
        }
        move_robot(lin_x, ang_z);
    }

    void move_robot(float lin_x, float ang_z) {
        ROS_INFO_STREAM("Moving the robot");

        // Request centered joint angles [1.57, 1.57]
        ball_chaser::DriveToTarget srv;
        srv.request.linear_x = lin_x;
        srv.request.angular_z = ang_z;

        // Call the safe_move service and pass the requested joint angles
        if (!client_.call(srv))
            ROS_ERROR("Failed to call service safe_move");
    }
};


int main(int argc, char** argv)
{
    // Initialize the arm_mover node and create a handle to it
    ros::init(argc, argv, "process_image");

    //Create an object of class SubscribeAndClient that will take care of everything
    SubscribeAndClient SACObject;

    ROS_INFO("Ready to find white ball");

    // Handle ROS communication events
    ros::spin();

    return 0;
}
