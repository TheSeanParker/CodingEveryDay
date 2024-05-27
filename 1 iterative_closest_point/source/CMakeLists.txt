cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(iterative_closest_point)
set(PCL_DIR "/home/deploy/livox_lidar/pcl-pcl-1.8.0/build")
find_package(PCL 1.8 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (iterative_closest_point iterative_closest_point.cpp)
target_link_libraries (iterative_closest_point ${PCL_LIBRARIES})
add_executable (iterative_closest_point_demo iterative_closest_point_demo.cpp)
target_link_libraries (iterative_closest_point_demo ${PCL_LIBRARIES})


