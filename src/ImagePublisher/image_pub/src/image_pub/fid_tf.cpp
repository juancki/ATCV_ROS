#include <tf/transform_broadcaster.h>




void poseCallback(const fiducial_msgs::FiducialTransform::ConstPtr &msg){
  static tf::TransformBroadcaster br;
  br.sendTransform(tf::StampedTransform(msg->transform, ros::Time::now(), "world", msg->id));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "from_fid_to_tf");

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/fiducial_transforms", 10, &poseCallback);

  ros::spin();
  return 0;
};
