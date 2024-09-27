cmake_minimum_required(VERSION 3.20)

project(condition)

add_custom_target(debug-gen-exp ALL
    COMMAND ${CMAKE_COMMAND} -E echo 
        "Is Debug: <$<IF:$<CONFIG:Debug>,Yes,No>$<ANGLE-R>"
    VERBATIM
)