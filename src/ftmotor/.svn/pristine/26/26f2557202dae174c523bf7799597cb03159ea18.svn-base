
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Point32.h>


#include <sstream>

float steering_info[3]={0.0,0.0,0.0};

void paveInfoCallback(const geometry_msgs::Point32& steerinfo)
  {steering_info[0] = steerinfo.x;
  steering_info[1] =steerinfo.y;

  }
int main(int argc, char **argv)
{

  ros::init(argc, argv, "Posi_Vel_pubandsub");// the name of node

  ros::NodeHandle n;

  ros::Publisher commands_pub = n.advertise<geometry_msgs::Point32>("gimbal_commands", 100);
  ros::Subscriber po_ve_sub = n.subscribe("/place_velocity_info", 1, paveInfoCallback);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::Point32 msg;
    msg.x=0.0;
    msg.y=30.0;
    msg.z=0.0;

    commands_pub.publish(msg);
    ros::Duration(12.0).sleep();

    msg.x=9.42;
    msg.y=70.0;
    msg.z=0.0;
    ROS_INFO("publishertest%f_%f_%f", msg.x,msg.y,msg.z);
    commands_pub.publish(msg);
    ros::Duration(8.0).sleep();

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
