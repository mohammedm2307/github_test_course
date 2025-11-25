#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "publishar_node_turtle_forwardcp");
    ros::NodeHandle n;
    
    
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    
    ros::Rate rate(2); 
    geometry_msgs::Twist var;

    ros::Rate loop_rate(10); 

    while (ros::ok())
    {
        var.linear.x = 0.5; 
        pub.publish(var);   
        ros::spinOnce();
        loop_rate.sleep();  
    }

    return 0;
}