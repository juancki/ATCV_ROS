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
  // cv::Size s = mat.size();
  // height: 1080
  // width: 1920
  // D: [0.0, 0.0, 0.0, 0.0, 0.0]
  // K: [1.0, 0.0, 960.0, 0.0, 1.0, 540.0, 0.0, 0.0, 1.0]
  // R: [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
  // P: [1.0, 0.0, 960.0, 0.0, 0.0, 1.0, 540.0, 0.0, 0.0, 0.0, 1.0, 0.0]
  ROS_INFO(argv[1]);
  ROS_INFO("IMAGE HEIGHT %d",image.rows);
  double q = 10000.0;
  double  k[] = {q, 0, image.cols/2,  0, q, image.rows/2,0,0 , 1};
  double p [] = {q, 0.0,  image.cols/2, 0.0, 0.0, q,  image.rows/2.0, 0.0, 0.0, 0.0, q, 0.0};
  cv::waitKey(30);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  // Creating info message
  sensor_msgs::CameraInfo msg_info = sensor_msgs::CameraInfo();
  msg_info.height = image.rows;
  msg_info.width = image.cols;
  for (int i = 0 ; i < 9; i++)
    msg_info.K[i] = k[i];
  for (size_t i = 0; i < 12; i++)
    msg_info.P[i] = p[i];
  msg_info.distortion_model = "plumb_bob";
  msg_info.D.resize(5, 0.0);

  //
  static tf::TransformBroadcaster br;

  ros::Rate loop_rate(1);
  while (nh.ok()) {
    pub.publish(msg);
    pub_info.publish(msg_info);
    ros::spinOnce();
    loop_rate.sleep();
    // sendTransform(self, translation, rotation, time, child, parent)
  }
}
