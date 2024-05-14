cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Define project name
project(mutex_project)
 
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
 
## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS
    thread
)
 
if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()
 
include_directories(${Boost_INCLUDE_DIRS})
# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} boost.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})