cmake_minimum_required(VERSION 2.6)

project(gtsamexamples CXX C)

# option: whether turn on Matlab toolbox
option(EXAMPLES_BUILD_MATLAB_TOOLBOX "whether build matlab toolbox" OFF)
# set(GTSAM_DIR "/home/deploy/gtsam-4.0.1/gtsam-4.0.1/build")

find_package(GTSAM REQUIRED) # Uses installed package
if(GTSAM_FOUND)  
  message(STATUS "Found GTSAM ${GTSAM_VERSION}")#打印出GTSAM的版本
else()
  message(STATUS "GTSAM Not Found")
endif()
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${GTSAM_INCLUDE_DIRS}
)
# INCLUDE_DIRECTORIES("/usr/include/eigen3")  #include也可以使用绝对路径的形式
set(GTSAM_LIBRARIES gtsam)   # TODO: automatic search libs

add_executable(isam ${CMAKE_SOURCE_DIR}/isam.cpp)
target_link_libraries(isam
    ${Boost_LIBRARIES}
    ${GTSAM_LIBRARIES}
)

