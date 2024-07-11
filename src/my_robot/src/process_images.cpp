#include "ros/ros.h"
#include "my_robot/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z)
{
    my_robot::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv)) {
        ROS_ERROR("Failed to call service command_robot");
    }
}

void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;
    bool ball_found = false;
    int column_index = -1;

    for (int i = 0; i < img.height * img.step; i += 3) {
        if (img.data[i] == white_pixel && img.data[i + 1] == white_pixel && img.data[i + 2] == white_pixel) {
            ball_found = true;
            column_index = i % img.step;
            break;
        }
    }

    if (ball_found) {
        if (column_index < img.step / 3) {
            drive_robot(0.0, 0.5);  // Turn left
        } else if (column_index > img.step * 2 / 3) {
            drive_robot(0.0, -0.5); // Turn right
        } else {
            drive_robot(0.5, 0.0);  // Move forward
        }
    } else {
        drive_robot(0.0, 0.0);  // Stop
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
    client = n.serviceClient<my_robot::DriveToTarget>("/my_robot/command_robot");
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
    ros::spin();

    return 0;
}
