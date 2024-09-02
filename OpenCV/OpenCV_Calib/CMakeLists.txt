# cmake for OpenCV Cookbook 3rd edition chapter 11
# your opencv/build directory should be in your system PATH

# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

# add opencv package to the project
find_package( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} ) 

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# add executable
add_executable( calibrate calibrate.cpp CameraCalibratorClass.cpp)
add_executable( cameraPose cameraPose.cpp)
# add_executable( estimateE estimateE.cpp triangulate.cpp)
# add_executable( stereoMatcher stereoMatcher.cpp)

# link libraries
target_link_libraries( calibrate ${OpenCV_LIBS})
target_link_libraries( cameraPose ${OpenCV_LIBS})
# target_link_libraries( estimateE ${OpenCV_LIBS})
# target_link_libraries( stereoMatcher ${OpenCV_LIBS})

# copy required images to every directory with executable
SET (IMAGES ${CMAKE_SOURCE_DIR}/images/bench2.jpg
            ${CMAKE_SOURCE_DIR}/images/soup1.jpg
            ${CMAKE_SOURCE_DIR}/images/soup2.jpg
            ${CMAKE_SOURCE_DIR}/images/brebeuf1.jpg
            ${CMAKE_SOURCE_DIR}/images/brebeuf2.jpg			
            calib.xml)

