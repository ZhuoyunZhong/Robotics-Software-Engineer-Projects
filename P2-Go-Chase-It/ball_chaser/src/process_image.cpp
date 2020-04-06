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

    // This callback function executes when new image comes in
    void process_image_callback(const sensor_msgs::Image img){
        // White ball color
        int white_pixel = 255;
        // Containers
        float lin_x = 0.0;
        float ang_z = 0.0;
        float ball_pos = 0.5;

        bool white_ball = false;

        // Loop through each pixel in the image and check if its equal to the first one
        for (int i = 0; i < img.height * img.step; i=i+3) {
            if (img.data[i] == 255 && img.data[i+1] == 255 && img.data[i+2] == 255) {
                ROS_INFO("Ball found");
                white_ball = true;

                // Calculate where the ball is
                ball_pos = (i % img.step) / float(img.step);

                break;
            }
        }

        // If the white ball is found
        if (white_ball == true) {
            lin_x = 1.0;
            if (ball_pos < 0.333) {
                ang_z = 5;
            }
            else if (ball_pos > 0.667) {
                ang_z = -5;
            }
        }
        move_robot(lin_x, ang_z);
    }

    // Move the robot
    void move_robot(float lin_x, float ang_z) {

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
