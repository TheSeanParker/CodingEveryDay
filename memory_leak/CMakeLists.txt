cmake_minimum_required(VERSION 2.8.3)
project(lio_sam)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -pthread")

set(CMAKE_CXX_FLAGS "-fsanitize=undefined,address,leak -fno-omit-frame-pointer")
# set(CMAKE_CXX_FLAGS "-fsanitize=address -g")
set(PCL_DIR "/home/deploy/livox_lidar/pcl-pcl-1.8.0/build")

find_package(catkin REQUIRED COMPONENTS
  tf
  roscpp
  rospy
  cv_bridge
  # pcl library
  pcl_conversions
  # msgs
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  message_generation
  visualization_msgs
)

find_package(OpenMP REQUIRED)
find_package(PCL REQUIRED QUIET)
find_package(OpenCV REQUIRED QUIET)
find_package(GTSAM REQUIRED QUIET)
find_package(Boost REQUIRED COMPONENTS timer)

# add_message_files(
#   DIRECTORY msg
#   FILES
#   cloud_info.msg
# )

# add_service_files(
#   DIRECTORY srv
#   FILES
#   save_map.srv
# )

generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs
  nav_msgs
  sensor_msgs
)

# catkin_package(
#   INCLUDE_DIRS include
#   DEPENDS PCL GTSAM

#   CATKIN_DEPENDS
#   std_msgs
#   nav_msgs
#   geometry_msgs
#   sensor_msgs
#   message_runtime
#   message_generation
#   visualization_msgs
# )

# include directories
include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
	${GTSAM_INCLUDE_DIR}
)

# link directories
link_directories(
	include
	${PCL_LIBRARY_DIRS}
  ${OpenCV_LIBRARY_DIRS}
  ${GTSAM_LIBRARY_DIRS}
)

###########
## Build ##
###########


# IMU Preintegration
add_executable(${PROJECT_NAME}  heap_leak.cpp)
# target_link_libraries(heap_leak)
