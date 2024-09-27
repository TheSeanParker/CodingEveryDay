cmake_minimum_required(VERSION 3.20)

project(a)

function(print_link_libraries tgt)
    get_target_property(res ${tgt} LINK_LIBRARIES)
    message("${tgt} LINK_LIBRARIES: ${res}")
    get_target_property(res ${tgt} INTERFACE_LINK_LIBRARIES)
    message("${tgt} INTERFACE_LINK_LIBRARIES: ${res}")
endfunction()

add_library(a SHARED a.c)

add_library(b SHARED b.c)
target_link_libraries(b ${MY_LINK_OPTION} a)
print_link_libraries(b)

add_executable(c c.c)
target_link_libraries(c PRIVATE b)
print_link_libraries(c)