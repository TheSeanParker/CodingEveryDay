cmake_minimum_required(VERSION 2.8.3)
project(livox_relocalization)

SET(CMAKE_BUILD_TYPE "Debug")

set(PCL_DIR "/home/deploy/livox_lidar/pcl-pcl-1.8.0/build")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -std=c++0x -std=c++14 -fexceptions -Wno-unused-local-typedefs")

find_package(OpenMP QUIET)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   ${OpenMP_C_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  sensor_msgs
  roscpp
  rospy
  std_msgs
  pcl_ros
  tf)

find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
	${catkin_INCLUDE_DIRS} 
        ${EIGEN3_INCLUDE_DIR}
	${PCL_INCLUDE_DIRS})

catkin_package(
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs
  DEPENDS EIGEN3 PCL OpenCV
)



add_executable(livox_scanRegistration src/scanRegistration.cpp)
target_link_libraries(livox_scanRegistration ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS})

# add_executable(livox_laserMapping src/laserMapping.cpp)
# target_link_libraries(livox_laserMapping ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS})


