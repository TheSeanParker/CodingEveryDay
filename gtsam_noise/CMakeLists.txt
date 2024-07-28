cmake_minimum_required(VERSION 2.6)

project(gtsamexamples CXX C)

# option: whether turn on Matlab toolbox
option(EXAMPLES_BUILD_MATLAB_TOOLBOX "whether build matlab toolbox" OFF)

find_package(Eigen3 REQUIRED)
find_package(GTSAM REQUIRED) 

if(GTSAM_FOUND)  
  message(STATUS "Found GTSAM ${GTSAM_VERSION}")#打印出GTSAM的版本
else()
  message(STATUS "GTSAM Not Found")
endif()
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${GTSAM_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
)
set(GTSAM_LIBRARIES gtsam)   # TODO: automatic search libs

add_executable(gtsam_noise ${CMAKE_SOURCE_DIR}/gtsam_noise.cpp)
target_link_libraries(gtsam_noise ${Boost_LIBRARIES}  ${GTSAM_LIBRARIES})
