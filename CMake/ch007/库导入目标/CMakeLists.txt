cmake_minimum_required(VERSION 3.20)

project(import-boost)

add_library(boost-regex STATIC IMPORTED)

if(WIN32)
    set(BOOST_REGEX_LIB_PATH 
        "C:/boost/stage/lib/libboost_regex-vc142-mt-gd-x64-1_74.lib")
    set(BOOST_INCLUDE_DIR "C:/boost")
else()
    set(BOOST_REGEX_LIB_PATH 
        "$ENV{HOME}/boost/stage/lib/libboost_regex.a")
    set(BOOST_INCLUDE_DIR "$ENV{HOME}/boost")
endif()

# 设置boost-regex目标的头文件目录的使用要求
target_include_directories(boost-regex INTERFACE ${BOOST_INCLUDE_DIR})

# 设置boost-regex目标的导入路径
set_target_properties(boost-regex PROPERTIES 
    IMPORTED_LOCATION "${BOOST_REGEX_LIB_PATH}")

add_executable(main "../../ch001/链接Boost/main.cpp")

# 声明main的构建要求：链接boost-regex库，也就是说
# 将boost-regex导入库的使用要求作为main的构建要求
target_link_libraries(main boost-regex)