cmake_minimum_required(VERSION 2.8.3)
project(camera_detect)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_definitions(-std=c++11 -g -O1 -ftree-vectorize -march=native)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    tf
    message_filters
    cv_bridge
    sensor_msgs
    image_transport
    message_generation
    std_msgs
    geometry_msgs
    visualization_msgs
)


# add_message_files(

# )

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)



set(OpenCV_DIR "/usr/share/OpenCV")

find_package(OpenCV REQUIRED)

find_package(Eigen3 REQUIRED)

catkin_package(
    CATKIN_DEPENDS message_runtime
)


include_directories(${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_definitions(${EIGEN_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(usbcam_aruco_detect src/usbcam_aruco_detect.cpp)
add_dependencies(usbcam_aruco_detect    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(usbcam_aruco_detect ${OpenCV_LIBS} ${catkin_LIBRARIES} )

add_executable(consensus_offb src/consensus_offb.cpp)
add_dependencies(consensus_offb        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(consensus_offb ${catkin_LIBRARIES} )

add_executable(path_follow_offb src/path_follow_offb.cpp)
add_dependencies(path_follow_offb        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(path_follow_offb ${catkin_LIBRARIES} )

add_executable(target_position_node src/target_position.cpp)
add_dependencies(target_position_node        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(target_position_node ${catkin_LIBRARIES} ${OpenCV_LIBS})




