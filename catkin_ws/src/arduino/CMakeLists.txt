cmake_minimum_required(VERSION 2.8.3)
project(arduino)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  rosserial_arduino
  rosserial_client
  sensor_msgs
)

catkin_package()

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

rosserial_configure_client(
  DIRECTORY firmware
  TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
)

rosserial_add_client_target(firmware control ALL)
rosserial_add_client_target(firmware control-upload)
