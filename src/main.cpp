// #include "LIVMapper.h"

// int main(int argc, char **argv)
// {
//   std::cout << "===== Foxy MAIN =====" << std::endl;
//   rclcpp::init(argc, argv);
//   rclcpp::NodeOptions options;
//   rclcpp::Node::SharedPtr nh;
//   image_transport::ImageTransport it_(nh);
//   LIVMapper mapper(nh, "laserMapping");
//   mapper.initializeSubscribersAndPublishers(nh, it_);
//   mapper.run(nh);
//   rclcpp::shutdown();
//   return 0;
// }

#include "LIVMapper.h"
#include <iostream>

int main(int argc, char **argv)
{
  std::cout << "===== Foxy MAIN START =====" << std::endl;

  rclcpp::init(argc, argv);

  std::cout << "rclcpp init done" << std::endl;

  // ✅ 直接创建 node（不要先声明）
  auto nh = std::make_shared<rclcpp::Node>("laserMapping");

  std::cout << "After create node, nh ptr = " << nh.get() << std::endl;

  // ✅ ROS2 必须 declare
  nh->declare_parameter<std::string>("config_file", "");

  std::cout << "Node created successfully" << std::endl;

  try
  {
    std::cout << "Creating ImageTransport..." << std::endl;
    image_transport::ImageTransport it_(nh);

    std::cout << "Creating LIVMapper..." << std::endl;
    LIVMapper mapper(nh, "laserMapping");

    std::cout << "Initializing pub/sub..." << std::endl;
    mapper.initializeSubscribersAndPublishers(nh, it_);

    std::cout << "Running mapper..." << std::endl;
    std::cout << "rclcpp ok? " << rclcpp::ok() << std::endl;
    mapper.run(nh);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }

  std::cout << "Shutting down..." << std::endl;
  rclcpp::shutdown();

  return 0;
}