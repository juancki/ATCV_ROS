#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

/*
 * Usage
 * $ rosrun image_transport_tutorial my_publisher path/to/some/image.jpg
 */
int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
  ros::Publisher pub_info = nh.advertise<sensor_msgs::CameraInfo>("camera/camera_info",1);
  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  double  k[] = {1060, 0, image.cols/2,  0, 1060, image.cols/2,0,0 , 1};
  cv::waitKey(30);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
  sensor_msgs::CameraInfo msg_info = sensor_msgs::CameraInfo();
  msg_info.height = image.rows;
  msg_info.width = image.cols;
  for (int i = 0 ; i < 9; i++)
    msg_info.K[i] = k[i];

  ros::Rate loop_rate(1);
  while (nh.ok()) {
    pub.publish(msg);
    pub_info.publish(msg_info);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
