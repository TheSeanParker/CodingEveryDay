cmake_minimum_required(VERSION 3.20)

project(link-only)

add_library(B SHARED dummy.c)
add_library(A STATIC dummy.c)

target_link_libraries(A PRIVATE B)

get_target_property(res A INTERFACE_LINK_LIBRARIES)
message("${res}") # 输出：$<LINK_ONLY:B>