
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Point32.h>
#include <sstream>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

#define PI 3.14159265

float current_v = 0.f;
float current_p = 0.f;
bool fisrt_recorded = false;
bool fisrt_img_get = false;
float start_p = 0.f;

const float linear_v_ob_start = 1.f;
const float linear_v_ob_max = 10.f;

bool save_img_trigger = false;
bool waiting_for_right_position = false;
bool in_right_position = false;
bool save_first_img = true;
float v_now = 0.f;

ros::Publisher commands_pub;

void motorCallback(const geometry_msgs::Point32& msg)
{
  current_p = msg.x;
  current_v = msg.y;
  if(!fisrt_recorded){
    start_p = current_p;
    fisrt_recorded = true;
  }
  if(waiting_for_right_position)
  {
    if(fabs(current_p - start_p) < 0.08)  //error limit: 0.02 rad = 1 degree
    {
      waiting_for_right_position = false;
      in_right_position = true;
    }
  }
   
}

void imgCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImageConstPtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg);
    fisrt_img_get = true;
  }
  catch (cv_bridge::Exception& e)
  {
     ROS_ERROR("cv_bridge exception: %s", e.what());
     return;
  }

    cv::Mat depth_img = cv_ptr->image;
    int nr = depth_img.rows;
    int nc = depth_img.cols;
    cv::Mat depth_uint(nr, nc, CV_8UC1, cv::Scalar::all(0));

    for(int i=0; i<nr ;i++)
    {
        unsigned short *inDepth = depth_img.ptr<unsigned short>(i); // float
        uchar* inDepth_uint = depth_uint.ptr<uchar>(i);

        for(int j=0; j<nc; j++)
        {
            // ROS_INFO("%d", inDepth[j]);
            if (inDepth[j] > 9000 || inDepth[j] != inDepth[j]) {
                inDepth_uint[j] = 0;
            }
            else {
                inDepth_uint[j] = (uchar)floor(inDepth[j] /1000.f * 28) ; // 56 = 256/4.5
            }
        }
    }

    cv::Mat depth_3_channels = cv::Mat(nr, nc, CV_8UC3);
    cv::cvtColor(depth_uint, depth_3_channels, CV_GRAY2BGR);

    cv::imshow("Monitor", depth_3_channels);
    
    if(in_right_position)
    {
        in_right_position = false;
        string name = to_string((int)v_now);
        string img_name = name+".png";
        string csv_name = name+".csv";

        cv::imwrite(img_name, depth_3_channels);

        ofstream csv_file(csv_name);
        
        int number_to_write = 0;
        for(int i=0; i<nr ;i++)
        {
            unsigned short *inDepth = depth_img.ptr<unsigned short>(i); // float
            for(int j=0; j<nc; j++)
            {
                // ROS_INFO("%d", inDepth[j]);
                if (inDepth[j] == inDepth[j]) {
                    number_to_write = inDepth[j];
                }
                else number_to_write = 0;
                
                string content_this = to_string(number_to_write) + ",";
                csv_file << content_this;
            }
            csv_file << "\n";         
        }
        csv_file.close();
    }

    if(save_first_img)
    {   
        save_first_img = false;
        string name = "0";
        string img_name = name+".png";
        string csv_name = name+".csv";

        cv::imwrite(img_name, depth_3_channels);
        ofstream csv_file(csv_name);
        
        int number_to_write = 0;
        for(int i=0; i<nr ;i++)
        {
            unsigned short *inDepth = depth_img.ptr<unsigned short>(i); // float
            for(int j=0; j<nc; j++)
            {
                // ROS_INFO("%d", inDepth[j]);
                if (inDepth[j] == inDepth[j]) {
                    number_to_write = inDepth[j];
                }
                else number_to_write = 0;
                
                string content_this = to_string(number_to_write) + ",";
                csv_file << content_this;
            }
            csv_file << "\n";    
        }
        csv_file.close();

    }
    
    cv::waitKey(5);
}

void move_to(float p, float v_cmd)
{
  geometry_msgs::Point32 msg;
  msg.x=p;
  msg.y=v_cmd * 10;
  msg.z=0.0;
  commands_pub.publish(msg);
}

float vel_to_rate_cmd(float ob_dist, float vel)
{
  float v_rad = vel / ob_dist;
  float result = v_rad / PI * 60.f;
  if(result < 72.f) return result;
  else{
    ROS_ERROR("Desired velocity too large for this ob_dist!!");
    return 72.f;
  }
}

float speed_after_change_direction()
{ 
    static float linear_v_ob = linear_v_ob_start;
    float pos, vel;
    if(current_p < start_p) pos= start_p + PI/4.0;
    else pos= start_p - PI/4.0;

    vel= vel_to_rate_cmd(3.0, linear_v_ob);  // l = 3.0m.
    move_to(pos, vel);
    
    linear_v_ob += 1.f;
    return linear_v_ob - 1.f;
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "blur_test");// the name of node

  ros::NodeHandle n;

  commands_pub = n.advertise<geometry_msgs::Point32>("gimbal_commands", 1);
  ros::Subscriber po_ve_sub = n.subscribe("/place_velocity_info", 1, motorCallback);
  ros::Subscriber img_sub = n.subscribe("/camera/depth/image_rect_raw", 1, imgCallback);

  ros::Rate loop_rate(50);

  while(!fisrt_recorded || !fisrt_img_get)
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  move_to(start_p + PI/4.0, 60);
  ros::Duration(3.0).sleep();
 
  int counter = 0; 
  

  while (ros::ok())
  {
    if(fisrt_recorded)
    {   
        counter ++;
        if(counter > 500)
        {
          counter = 0;
          waiting_for_right_position = true;
          v_now = speed_after_change_direction();
	  if(v_now > 10.f) break;  
        }
        
    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
