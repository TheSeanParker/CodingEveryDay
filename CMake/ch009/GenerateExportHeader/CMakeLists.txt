cmake_minimum_required(VERSION 3.20)
project(export-api)
include(GenerateExportHeader)

add_library(print SHARED print.c)
generate_export_header(print
    # DEFINE_NO_DEPRECATED # 取消注释以定义忽略弃用接口宏
) # 导出头文件会被生成到二进制目录中

# 将当前二进制目录加到头文件搜索目录中
target_include_directories(print PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# 定义print_EXPORTS宏，表明正在构建该库（若不定义，则表示使用该库）
target_compile_definitions(print PRIVATE print_EXPORTS)

# 设置目标属性，默认隐藏符号和内联函数
set_target_properties(print PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
)
# 也可以通过下面两个变量，设置上述两个目标属性的默认值
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# 主程序
add_executable(main main.c)
target_link_libraries(main PRIVATE print)
if(MSVC)
    # 为MSVC编译器启用级别3的警告
    target_compile_options(main PRIVATE /W3)
endif()

# 静态库
add_library(print_static STATIC print.c)
target_include_directories(print_static PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(print_static PUBLIC PRINT_STATIC_DEFINE)
