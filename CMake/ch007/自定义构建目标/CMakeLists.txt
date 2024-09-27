cmake_minimum_required(VERSION 3.20)

project(custom-target)

add_custom_target(a
    ${CMAKE_COMMAND} -E echo "custom target: a"
    SOURCES a.c
    VERBATIM)

add_custom_target(b ALL
    ${CMAKE_COMMAND} -E echo "custom target: b"
    SOURCES b.c
    VERBATIM)