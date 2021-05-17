/***
 * Used to display FPS in frame
 * tested on usb cam
 *
 * results: about 100+ fps
 *
 * Tonser
 */
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <csignal>


using namespace cv;
using namespace std;

bool flag = true;

void shutdown_handler(int)
{
    cout<<"shutdown"<<endl;
    flag = false;
} 

void watchSignal() {
    signal(SIGINT, shutdown_handler);
    signal(SIGTERM, shutdown_handler);
    signal(SIGKILL, shutdown_handler);
    signal(SIGQUIT, shutdown_handler);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);
    ros::Rate loop_rate(30);

    VideoCapture capture(0);
    if (!capture.isOpened()) {
        printf("[%s][%d]could not load video data...\n", __FUNCTION__, __LINE__);
        return -1;
    }

    Mat frame;
    int last_time = 0;
    double t;
    double fps;
    int i = 0;
    char disp_fps[10];
    string filename = "";
    while (flag) {
        t = (double)cvGetTickCount();
        if (waitKey(5) == 27) {
            break;
        }
        watchSignal();

        if (capture.isOpened())
        {
            capture >> frame;
            sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
            fps = 1.0 / t;

            sprintf(disp_fps, "%.2f", fps);      // 帧率保留两位小数
            string fpsString("FPS:");
            fpsString += disp_fps;                    // 在"FPS:"后加入帧率数值字符串
            // 将帧率信息写在输出帧上
            putText(frame, // 图像矩阵
                    fpsString,                  // string型文字内容
                    cv::Point(5, 40),           // 文字坐标，以左下角为原点
                    cv::FONT_HERSHEY_COMPLEX,   // 字体类型
                    1.0, // 字体大小
                    cv::Scalar(255, 0, 0));       // 字体颜色

            // filename = "/home/up/Desktop/image4/" + to_string(i) + ".jpg";
            // imwrite(filename,frame);
            imshow("Camera FPS", frame);
            // i++;
            // cout << "i = " << i << endl; 
            pub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }
    cv::destroyAllWindows();
    waitKey(0);
    return 0;
}