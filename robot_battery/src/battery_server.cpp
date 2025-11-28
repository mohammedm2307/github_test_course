#include "ros/ros.h"
#include "robot_battery/BatteryStatus.h"  // Auto-generated from BatteryStatus.srv

// Global battery level (simulated)
float battery_level = 100.0;

ros::ServiceServer service;

// Service callback function
bool handleBatteryRequest(
    robot_battery::BatteryStatus::Request &req,
    robot_battery::BatteryStatus::Response &res
) 

{
    // Simulate battery drain (1% per request)
    if (battery_level > 0.0) {
        battery_level -= 1.0;
    }

    // Set response
    res.battery_level = battery_level;
    ROS_INFO("Battery level: %.2f%%", res.battery_level);

    return true;
}

int main(int argc, char **argv) {
    // Initialize ROS node
    ros::init(argc, argv, "battery_server");
    ros::NodeHandle nh;

    // Advertise the service
    service = nh.advertiseService("get_battery_status",handleBatteryRequest);

    ROS_INFO("Battery status service is ready.");

    // Keep the node running
    ros::spin();

    return 0;
}