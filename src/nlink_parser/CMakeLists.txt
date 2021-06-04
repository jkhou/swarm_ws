cmake_minimum_required(VERSION 3.5)
project(nlink_parser)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)
add_definitions(-std=c++14)
include_directories("/usr/include/eigen3")
include_directories("/usr/include/glog")
include_directories("/usr/local/lib/cmake/Ceres/")


find_package(Ceres REQUIRED)
find_package(Eigen3 3.3 REQUIRED)
find_package(gflags 2.2.0)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    geometry_msgs
    message_generation
    roslib
    )

## Generate messages in the 'msg' folder
add_message_files(
    FILES
    LinktrackAnchorframe0.msg
    LinktrackNode0.msg
    LinktrackNode1.msg
    LinktrackNode2.msg
    LinktrackNodeframe0.msg
    LinktrackNodeframe1.msg
    LinktrackNodeframe2.msg
    LinktrackNodeframe3.msg
    LinktrackTag.msg
    LinktrackTagframe0.msg
    TofsenseCascade.msg
    TofsenseFrame0.msg
    LinktrackAoaNode0.msg
    LinktrackAoaNodeframe0.msg
    SwarmPos.msg
    UWBDisStamped.msg
    SwarmInfoStamped.msg
    SwarmPosStamped.msg
    )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
    DEPENDENCIES
    std_msgs
    geometry_msgs
    )

catkin_package(
    #  INCLUDE_DIRS include
    #  LIBRARIES nlink
    CATKIN_DEPENDS message_runtime
    #  DEPENDS system_lib
    )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    src/utils
    )
add_library(PIDlib
        src/linktrack/PID.h
        src/linktrack/PID.cpp)

set(nutils "nutils")
add_library(${nutils}
    src/utils/protocol_extracter/nprotocol_base.cpp
    src/utils/protocol_extracter/nprotocol_extracter.cpp
    src/utils/nlink_unpack/nlink_utils.c
    src/utils/nlink_unpack/nlink_linktrack_anchorframe0.c
    src/utils/nlink_unpack/nlink_linktrack_tagframe0.c
    src/utils/nlink_unpack/nlink_linktrack_nodeframe0.c
    src/utils/nlink_unpack/nlink_linktrack_nodeframe1.c
    src/utils/nlink_unpack/nlink_linktrack_nodeframe2.c
    src/utils/nlink_unpack/nlink_linktrack_nodeframe3.c
    src/utils/nlink_unpack/nlink_tofsense_frame0.c
    src/utils/nlink_unpack/nlink_linktrack_aoa_nodeframe0.c
    src/utils/init_serial.cpp
    src/utils/nlink_protocol.cpp
    src/utils/nutils.cpp
)
target_link_libraries(${nutils}
  ${catkin_LIBRARIES}
  serial
)

set(LINKTRACK_NAME "linktrack")
add_executable(${LINKTRACK_NAME}
    src/linktrack/init.cpp
    src/linktrack/main.cpp
    src/linktrack/protocols.cpp
        )
target_link_libraries(${LINKTRACK_NAME}
#    ${catkin_LIBRARIES}
    ${nutils}
    )
add_dependencies(${LINKTRACK_NAME} ${PROJECT_NAME}_generate_messages_cpp)


add_executable(uwb_recv src/linktrack/uwb_recv.cpp)
add_dependencies(uwb_recv   ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(uwb_recv ${nutils} )

add_executable(gs_uwb_recv src/linktrack/gs_uwb_recv.cpp)
add_dependencies(gs_uwb_recv   ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(gs_uwb_recv ${nutils} )

add_executable(circle_offb src/linktrack/circle_offb.cpp)
add_dependencies(circle_offb   ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(circle_offb ${nutils} ${catkin_LIBRARIES} PIDlib)

add_executable(swarm_state_est src/linktrack/swarm_state_est.cpp)
add_dependencies(swarm_state_est   ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(swarm_state_est ${nutils} glog ceres)



set(LINKTRACK_RVIZ_NAME "linktrack_rviz_converter")
add_executable(${LINKTRACK_RVIZ_NAME}
    src/linktrack/main_rviz_converter.cpp
    )
target_link_libraries(${LINKTRACK_RVIZ_NAME}
    ${nutils}
    )
add_dependencies(${LINKTRACK_RVIZ_NAME} ${PROJECT_NAME}_generate_messages_cpp)

set(TOFSENSE_NAME "tofsense")
add_executable(${TOFSENSE_NAME}
    src/tofsense/init.cpp
    src/tofsense/main.cpp
    )
target_link_libraries(${TOFSENSE_NAME}
#    ${catkin_LIBRARIES}
    ${nutils}
    )
add_dependencies(${TOFSENSE_NAME} ${PROJECT_NAME}_generate_messages_cpp)

set(LINKTRACK_AOA_NAME "linktrack_aoa")
add_executable(${LINKTRACK_AOA_NAME}
    src/linktrack_aoa/init.cpp
    src/linktrack_aoa/main.cpp
    src/linktrack/protocols.cpp
    )
target_link_libraries(${LINKTRACK_AOA_NAME}
#    ${catkin_LIBRARIES}
    ${nutils}
    )
add_dependencies(${LINKTRACK_AOA_NAME} ${PROJECT_NAME}_generate_messages_cpp)


#############
## Testing ##
#############
if(${CATKIN_ENABLE_TESTING})
    find_package(rostest REQUIRED)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    ## Add gtest based cpp test target and link libraries
    catkin_add_gtest(${PROJECT_NAME}-test
        src/linktrack/init.cpp
        src/linktrack/protocols.cpp
        src/tofsense/init.cpp
        src/linktrack_aoa/init.cpp
        test/test_nlink_parser.cpp
        )
endif()

if(TARGET ${PROJECT_NAME}-test)
    target_link_libraries(${PROJECT_NAME}-test  ${nutils})
endif()
