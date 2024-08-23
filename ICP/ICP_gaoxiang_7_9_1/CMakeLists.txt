cmake_minimum_required(VERSION 2.8)
project(vo1)

set(CMAKE_BUILD_TYPE "Release")
add_definitions("-DENABLE_SSE")
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 ${SSE_FLAGS} -msse4")
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules) 
message(STATUS ${CMAKE_MODULE_PATH})

find_package(OpenCV 3 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(G2O REQUIRED)
find_package(Sophus REQUIRED)

include_directories(
        ${EIGEN3_INCLUDE_DIRS}
        ${G2O_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Sophus_INCLUDE_DIRS}
)

# add_executable(pose_estimation_2d2d pose_estimation_2d2d.cpp)
# target_link_libraries(pose_estimation_2d2d ${OpenCV_LIBS})

# add_executable( triangulation triangulation.cpp extra.cpp) 

add_executable(triangulation triangulation.cpp)
target_link_libraries(triangulation ${OpenCV_LIBS})

add_executable(pose_estimation_3d2d pose_estimation_3d2d.cpp)
target_link_libraries(pose_estimation_3d2d
        g2o_core g2o_stuff
        ${OpenCV_LIBS}
        )

add_executable(pose_estimation_3d3d pose_estimation_3d3d.cpp)
target_link_libraries(pose_estimation_3d3d
                                           g2o_core g2o_stuff
                                          ${OpenCV_LIBS}
                                          )
