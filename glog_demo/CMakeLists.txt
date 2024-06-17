
cmake_minimum_required(VERSION 3.0)
project(PROJECT)
set(CMAKE_CXX_FLAGS"-std=c++11")
find_package(Glog REQUIRED)
include_directories( ${GLOG_INCLUDE_DIRS}) 
add_executable(log_test log_test.cpp)
target_link_libraries(
          log_test  glog
)
add_executable(static static.cpp)
target_link_libraries(
          static     glog::glog
)
add_executable(glog_mkdir glog_mkdir.cpp)
target_link_libraries(
          glog_mkdir    glog::glog
)
# https://cnlinxi.github.io/blog/develop/cpp/cpp%E5%B8%B8%E7%94%A8%E5%BA%93gflags_glog_gtest/