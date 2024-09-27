cmake_minimum_required(VERSION 3.20)

project(build_config_and_sources)

add_executable(main 
    $<$<CONFIG:Debug>:debug.c>
    $<$<CONFIG:Release>:release.c>
)