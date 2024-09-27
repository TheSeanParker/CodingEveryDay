cmake_minimum_required(VERSION 3.20)

project(comparison)

add_custom_target(debug-gen-exp ALL
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<EQUAL:0,-0>" # 输出：1
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<STREQUAL:0,-0>" # 输出：0
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<IN_LIST:2,1;2;3>" # 输出：1
    COMMAND ${CMAKE_COMMAND} -E echo
        "$<VERSION_LESS:1.1.2,1.2.0>" # 输出：1
)