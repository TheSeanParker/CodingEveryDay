cmake_minimum_required(VERSION 2.8.3)
project(core_nav)

set (CMAKE_CXX_STANDARD 14)

# find_package(Eigen3 REQUIRED)
# find_package(Ceres REQUIRED)
# message(STATUS CERES_VERSION: ${CERES_VERSION})
# message(STATUS CERES_INCLUDE_DIRS: ${CERES_INCLUDE_DIRS})
# message(STATUS CERES_LIBRARIES: ${CERES_LIBRARIES})

# include_directories(
#   ${CMAKE_SOURCE_DIR}
#   ${EIGEN3_INCLUDE_DIR}
#   ${CERES_INCLUDE_DIRS}
# )

#add_library(${PROJECT_NAME} src/classOdomotry.cpp)
# target_link_libraries(${PROJECT_NAME}
# )

add_executable(core_nav_fusion main.cpp   classOdomotry.cpp classOdomotry.h)

# executable file
# add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}.cpp)
#  target_link_libraries(${PROJECT_NAME}_node
##   ${PROJECT_NAME}
#   ${catkin_LIBRARIES}
#   ${OpenCV_LIBRARIES}
#   ${CERES_LIBRARIES}
#   ${Pangolin_LIBRARIES}
  #${PROTOBUF_LIBRARIES}
# )
