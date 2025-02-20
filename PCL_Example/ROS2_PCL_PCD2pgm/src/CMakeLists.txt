cmake_minimum_required(VERSION 3.8)
project(pcdtotxt)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

ADD_COMPILE_OPTIONS(-std=c++14)
set(CMAKE_CXX_FLAGS "-std=c++14 -O3")

add_definitions(-DROOT_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -std=c++0x -std=c++14 -fexceptions")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(Sophus_LIBRARIES "/home/deploy/env_pack_install/sophus_a621ff/build/libSophus.so")


message("Current CPU archtecture: ${CMAKE_SYSTEM_PROCESSOR}")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
  include(ProcessorCount)
  ProcessorCount(N)
  message("Processer number:  ${N}")

  if(N GREATER 4)
    add_definitions(-DMP_EN)
    add_definitions(-DMP_PROC_NUM=3)
    message("core for MP: 3")
  elseif(N GREATER 3)
    add_definitions(-DMP_EN)
    add_definitions(-DMP_PROC_NUM=2)
    message("core for MP: 2")
  else()
    add_definitions(-DMP_PROC_NUM=1)
  endif()
else()
  add_definitions(-DMP_PROC_NUM=1)
endif()

find_package(OpenMP QUIET)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   ${OpenMP_C_FLAGS}")

find_package(PythonLibs REQUIRED)
find_path(MATPLOTLIB_CPP_INCLUDE_DIRS "matplotlibcpp.h")
# ROS dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(livox_ros_driver2 REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(Sophus REQUIRED)
# Thirdparty libraries
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io)
find_package(GTSAM REQUIRED)
find_package(OpenCV REQUIRED)

if(GTSAM_FOUND)  
  message(STATUS "Found GTSAM ${GTSAM_VERSION}")
else()
  message(STATUS "GTSAM Not Found")
endif()
message(STATUS "PCL_INCLUDE_DIRS:" ${PCL_INCLUDE_DIRS})
message(STATUS "PCL_LIBRARY_DIRS:" ${PCL_LIBRARY_DIRS})
message(STATUS "PCL_DEFINITIONS:" ${PCL_DEFINITIONS})
message(STATUS "-------------EIGEN3_INCLUDE_DIRS:" ${EIGEN3_INCLUDE_DIRS})

set(dependencies
  rclcpp
  rclcpp_components
  geometry_msgs
  nav_msgs
  sensor_msgs
  std_msgs
  std_srvs
  visualization_msgs
  pcl_ros
  pcl_conversions
  livox_ros_driver2
  PCL
  GTSAM
  OpenCV
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(pcdtotxt pcdtotxt.cpp )

target_include_directories(pcdtotxt PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${PCL_INCLUDE_DIRS}
  ${GTSAM_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)
message("%%%%%%%%%%%%%%%%%%")
# target_link_libraries(pcdtotxt ${PCL_LIBRARIES} ${PYTHON_LIBRARIES} Eigen3::Eigen ${Sophus_LIBRARIES} gtsam)
target_link_libraries(pcdtotxt  ${PYTHON_LIBRARIES} Eigen3::Eigen ${Sophus_LIBRARIES} gtsam)

target_include_directories(pcdtotxt PRIVATE ${PYTHON_INCLUDE_DIRS})

list(APPEND EOL_LIST "foxy" "galactic" "eloquent" "dashing" "crystal")


ament_target_dependencies(pcdtotxt ${dependencies})

# ---------------- Install --------------- #
install(TARGETS pcdtotxt
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()