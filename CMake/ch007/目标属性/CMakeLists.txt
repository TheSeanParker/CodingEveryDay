cmake_minimum_required(VERSION 3.20)

project(target_property)

add_executable(main main.c)

# 设置main的目标属性
set_target_properties(main PROPERTIES 
    # 构建要求：将include加入头文件搜索目录
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
    # 构建要求：链接a库（即传递a库的使用要求到main中作为main的构建要求）
    LINK_LIBRARIES a
)

add_subdirectory(liba)