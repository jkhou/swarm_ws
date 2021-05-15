cmake_minimum_required(VERSION 2.8.3)
project(ftmotor)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_definitions(-std=c++11 -g -O3 -ftree-vectorize -march=native)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  serial
  std_msgs
  message_generation
  cv_bridge
  sensor_msgs
  image_transport
)

find_package(
OpenCV REQUIRED
)

add_message_files(
  FILES
  Flow.msg
  # Message2.msg
)


generate_messages(
  DEPENDENCIES
  std_msgs
)


catkin_package(
   CATKIN_DEPENDS message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES px4flow
#  CATKIN_DEPENDS roscpp serial std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}$
)

link_directories(lib)
link_libraries(libSCServo.a)

add_executable(motor_driver src/motor_driver.cpp)
target_link_libraries(motor_driver ${catkin_LIBRARIES})

add_executable(small_motor_driver src/small_motor_driver.cpp)
target_link_libraries(small_motor_driver ${catkin_LIBRARIES})

add_executable(small_motor_driver_fake_pose src/small_motor_driver_fake_pose.cpp)
target_link_libraries(small_motor_driver_fake_pose ${catkin_LIBRARIES})

add_executable(Posi_Vel_pubandsub src/Posi_Vel_pubandsub.cpp)
target_link_libraries(Posi_Vel_pubandsub ${catkin_LIBRARIES})

add_executable(Blur_test src/Blur_test.cpp)
target_link_libraries(Blur_test ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
