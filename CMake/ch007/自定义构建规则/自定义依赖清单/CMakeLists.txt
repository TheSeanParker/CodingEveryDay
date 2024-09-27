cmake_minimum_required(VERSION 3.20)

project(custom-depfile)

add_executable(main2 main2.c)

configure_file(mydep.d ${CMAKE_BINARY_DIR}/mydep.d)

add_custom_command(OUTPUT main2.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/main.c main2.c
    DEPENDS main.c
    DEPFILE mydep.d
)
