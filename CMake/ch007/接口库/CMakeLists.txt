cmake_minimum_required(VERSION 3.20)

project(myInterfaceLib)

add_library(myInterfaceLib INTERFACE)

# 声明myInterfaceLib的使用要求：头文件搜索目录应为include
target_include_directories(myInterfaceLib INTERFACE include)

add_executable(main main.c)

# 声明main的构建要求：链接myInterfaceLib库，也就是说
# 将myInterfaceLib接口库的使用要求作为main的构建要求
target_link_libraries(main myInterfaceLib)