cmake_minimum_required(VERSION 3.2)
project(MY_GRAND_PROJECT)
find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# target_link_libraries(pcd_write_test  ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} )
add_executable(kdtree kdtree.cpp) 
target_link_libraries(kdtree ${PCL_LIBRARIES})

add_executable(savePcd savePcd.cpp) 
target_link_libraries(savePcd ${PCL_LIBRARIES})
