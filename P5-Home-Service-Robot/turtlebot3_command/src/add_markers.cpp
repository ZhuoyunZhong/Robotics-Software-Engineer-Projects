#include "ros/ros.h"
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <std_msgs/Bool.h>

bool picked = false;
bool reached = false;

void reach_callback(const std_msgs::Bool& msg){
    if (msg.data != true){
        return;
    }

    if (picked == false){
        picked = true;
    }
    else {
        picked = false;
        reached = true;
    }
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Subscriber reached_sub = n.subscribe("/reach_position", 10, reach_callback);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    while (ros::ok()){
        ros::spinOnce();
        if (picked == true){
            continue;
        }
        
        visualization_msgs::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        // Set the namespace and id for this marker.  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
        marker.ns = "basic_shapes";
        marker.id = 0;

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
        marker.type = shape;

        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;

        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        if (reached == false){
            marker.pose.position.x = -3.0;
            marker.pose.position.y = -0.5;
            marker.pose.orientation.z = -0.707;
            marker.pose.orientation.w = 0.707;
        }
        else{
            marker.pose.position.x = 4.0;
            marker.pose.position.y = 0.0;
            marker.pose.orientation.z = 0.707;
            marker.pose.orientation.w = 0.707;
        }
        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;

        // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 0.0;
        marker.color.g = 0.0;
        marker.color.b = 1.0;
        marker.color.a = 0.8;

        marker.lifetime = ros::Duration(0.2);

        // Publish the marker
        while (marker_pub.getNumSubscribers() < 1){
            if (!ros::ok()){
                return 0;
            }
            sleep(1);
        }
        marker_pub.publish(marker);
    }
    return 0;
}
