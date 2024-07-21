cmake_minimum_required(VERSION 2.8.3)
project(lio_sam)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -pthread")

find_package(catkin REQUIRED COMPONENTS
  # pcl library
  pcl_conversions
)

find_package(OpenMP REQUIRED)
find_package(PCL REQUIRED QUIET)

# include library directories
include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
)
# include library file
link_directories(
	include
	${PCL_LIBRARY_DIRS}
)
# Range Image Projection
add_executable(transformPointCloud transformPointCloud.cpp)
add_dependencies(transformPointCloud ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(transformPointCloud ${catkin_LIBRARIES} ${PCL_LIBRARIES} )

