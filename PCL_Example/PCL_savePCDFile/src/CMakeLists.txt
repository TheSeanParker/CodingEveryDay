cmake_minimum_required(VERSION 3.2)
project(MY_GRAND_PROJECT)
# set(PCL_DIR "/home/deploy/livox_lidar/pcl-pcl-1.8.0/build")
find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# target_link_libraries(pcd_write_test  ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} )
add_executable(pcl_SavePcd PCL_SavePcd.cpp) 
target_link_libraries(pcl_SavePcd ${PCL_LIBRARIES})

