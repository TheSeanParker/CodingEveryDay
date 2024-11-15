cmake_minimum_required(VERSION 3.5.1)
project(lio_sam)

find_package(Boost REQUIRED COMPONENTS thread)

set(CMAKE_BUILD_TYPE "Release")
set( CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

set(GTSAM_USE_SYSTEM_EIGEN ON)
find_package(GTSAM)
# find_package(GTSAM REQUIRED QUIET)
if(GTSAM_FOUND)  
  message(STATUS "Found GTSAM ${GTSAM_VERSION}")
else()
  message(STATUS "GTSAM Not Found")
endif()
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  message_filters
  nav_msgs
  sensor_msgs
  message_generation
  message_runtime
  message_filters
  roscpp
  rospy
  rosbag
  std_msgs
  image_transport
  cv_bridge
  tf
)

#find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(OpenMP REQUIRED)
find_package(GTSAM REQUIRED QUIET)

# Python3,numpy
find_package(Python3 COMPONENTS Development NumPy)


include_directories(
	${catkin_INCLUDE_DIRS} 
	${PCL_INCLUDE_DIRS}
  ${CERES_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${GTSAM_INCLUDE_DIR})

catkin_package(
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs
  DEPENDS EIGEN3 PCL 
)

add_executable(PointRigidTransformationFactor src/PointRigidTransformationFactor.cpp) # 自定义因子（类似于GPS的一元因子）
target_link_libraries(PointRigidTransformationFactor ${catkin_LIBRARIES}  ${PCL_LIBRARIES} gtsam)

# add_executable(custom_factor src/custom_factor.cpp) # 自定义因子（类似于GPS的一元因子）
# target_link_libraries(custom_factor ${catkin_LIBRARIES}  ${PCL_LIBRARIES} gtsam)

add_executable(curveFitting src/curveFitting.cpp) # 曲线拟合
target_link_libraries(curveFitting ${OpenCV_LIBS} ${catkin_LIBRARIES}  ${PCL_LIBRARIES} gtsam Python3::Python Python3::NumPy)
target_include_directories(curveFitting PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})


add_executable(IcpFactor_gtsam src/IcpFactor_gtsam.cpp) # 自定义因子（类似于GPS的一元因子）
target_link_libraries(IcpFactor_gtsam ${catkin_LIBRARIES}  ${PCL_LIBRARIES} gtsam)

