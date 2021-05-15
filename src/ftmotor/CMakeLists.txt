cmake_minimum_required(VERSION 2.8.3)
project(ftmotor)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_definitions(-std=c++11 -g -O3 -ftree-vectorize -march=native)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  serial
  std_msgs
)

#find_package(
#OpenCV REQUIRED
#)

# add_message_files(
#   FILES
# )


#generate_messages(
#  DEPENDENCIES
#  std_msgs
#)


catkin_package(
   CATKIN_DEPENDS message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

link_directories(lib)
link_libraries(libSCServo.a)

add_executable(ft_servo_control src/ft_servo_control.cpp)
target_link_libraries(ft_servo_control ${catkin_LIBRARIES})
