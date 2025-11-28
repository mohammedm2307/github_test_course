#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <array>
#include <iostream>
#include <vector>

using namespace std;

// تعريف متغيرات لتخزين قراءات الليزر في الاتجاهات المختلفة
float front_laser;
float left_laser;
float right_laser;

// دالة الـ Callback لاستقبال بيانات الليزر
void laser_Callback(const sensor_msgs::LaserScan &msg) {
  // تخزين القراءات بناءً على زوايا الاندكس (0 للامام، 90 لليسار، 270 لليمين)
  // ملحوظة: الاندكسات دي بتعتمد على نوع الروبوت (TurtleBot3)
  front_laser = msg.ranges[0];
  left_laser = msg.ranges[90];
  right_laser = msg.ranges[270];

  // طباعة القراءات للتجربة (اختياري)
     std::cout << front_laser << right_laser << endl;
}

int main(int argc, char **argv) {

  // 1. تهيئة النود
  ros::init(argc, argv, "topics_quiz_node");

  ros::NodeHandle n;

  geometry_msgs::Twist vel;

  // 2. إنشاء Subscriber لقراءة الليزر
  ros::Subscriber sub = n.subscribe("/scan", 50, laser_Callback);
  
  // 3. إنشاء Publisher لإرسال أوامر الحركة
  ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
  
  ros::Rate loop_rate(50);

  while (ros::ok()) {
    
    // الحالة 1: الطريق سالك في كل الاتجاهات -> تحرك للأمام
    if (front_laser > 1.0 && right_laser > 1.0 && left_laser > 1.0) {
      vel.linear.x = 0.2;
      vel.angular.z = 0;
      ROS_INFO("move forward[%f]", front_laser);
    }
    
    // الحالة 2: عائق أمام الروبوت -> لف يسار
    // (السطر ده كان متغطى في الصورة، بس ده المنطق التكميلي للكود)
    else if (front_laser < 1.0 && right_laser > 1.0 && left_laser > 1.0) {
      vel.linear.x = 0.0;
      vel.angular.z = 0.2;
      ROS_INFO("turn left[%f]", right_laser);
    }
    
    // الحالة 3: عائق على اليسار (قريب من الحيطة) -> لف يمين للابتعاد
    else if (left_laser <= 1.0) {
      vel.linear.x = 0.0;
      vel.angular.z = -0.2;
      ROS_INFO("turn right[%f]", left_laser);
    }
    
    // تحديث ونشر السرعة
    ros::spinOnce();
    vel_pub.publish(vel);
    loop_rate.sleep();
  }

  return 0;
}