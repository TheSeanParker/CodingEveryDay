# cmake for OpenCV Cookbook 3rd edition chapter 10
# your opencv/build directory should be in your system PATH

# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)
set(project_name "OpenCV3Cookbook")

# set the project name
project("${project_name}")

# this is a C++11 project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add opencv package to the project
find_package( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} ) 
SET(OpenCV_LIBRARIES ${OpenCV_LIBS})

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
# add executable
add_executable( estimateF estimateF.cpp)
add_executable( robustmatching robustmatching.cpp)
add_executable( estimateH estimateH.cpp)
add_executable( matchingTarget matchingTarget.cpp)

# link libraries
target_link_libraries( estimateF ${OpenCV_LIBS})
target_link_libraries( robustmatching ${OpenCV_LIBS})
target_link_libraries( estimateH ${OpenCV_LIBS})
target_link_libraries( matchingTarget ${OpenCV_LIBS})

# copy required images to every directory with executable
SET (IMAGES ${CMAKE_SOURCE_DIR}/images/church01.jpg 
            ${CMAKE_SOURCE_DIR}/images/church02.jpg
            ${CMAKE_SOURCE_DIR}/images/church03.jpg
            ${CMAKE_SOURCE_DIR}/images/parliament1.jpg
            ${CMAKE_SOURCE_DIR}/images/parliament2.jpg
            ${CMAKE_SOURCE_DIR}/images/parliament3.jpg
            ${CMAKE_SOURCE_DIR}/images/cookbook1.bmp
            ${CMAKE_SOURCE_DIR}/images/objects.jpg)
FILE(COPY ${IMAGES} DESTINATION .)
FILE(COPY ${IMAGES} DESTINATION "Debug")
FILE(COPY ${IMAGES} DESTINATION "Release")
