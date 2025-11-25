#include "ros/ros.h"
#include "turtlesim/Pose.h"


void chatterCallback(const turtlesim::Pose::ConstPtr& msg)
{
    
    ROS_INFO("Robot's Position \n x: %f \n y: %f \n theta: %f", msg->x, msg->y, msg->theta);
}

int main(int argc, char **argv)
{
  
    ros::init(argc, argv, "pose_subscriber_node");

    
    ros::NodeHandle n;

   
    ros::Subscriber sub_chatter = n.subscribe("/turtle1/pose", 0.1, chatterCallback);

   
    ros::spin();

    return 0;
}