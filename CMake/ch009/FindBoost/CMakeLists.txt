cmake_minimum_required(VERSION 3.20)

project(find-boost)

if(WIN32)
    set(BOOST_ROOT "C:/boost_prebuilt") # 使用预编译的Boost库
    # set(BOOST_ROOT "C:/boost/stage") # 使用自己构建的Boost库
else()
    # set(BOOST_ROOT "$ENV{HOME}/boost") # 取消注释以使用自己构建的Boost库
endif()

find_package(Boost REQUIRED COMPONENTS regex)

add_executable(main "../../ch001/链接Boost/main.cpp")
target_link_libraries(main Boost::regex)