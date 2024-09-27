cmake_minimum_required(VERSION 3.20)

project(PRE_BUILD_vs_PRE_LINK)

add_executable(main main.c)

add_custom_command(TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "run PRE_BUILD"
    VERBATIM)

add_custom_command(TARGET main PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E echo "run PRE_LINK"
    VERBATIM)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "run POST_BUILD"
    VERBATIM)