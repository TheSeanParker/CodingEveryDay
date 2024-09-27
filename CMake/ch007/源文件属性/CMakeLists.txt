cmake_minimum_required(VERSION 3.20)

project(source_file_property)

add_subdirectory(a)
add_subdirectory(b)

set_source_files_properties(main.c DIRECTORY a
    PROPERTIES COMPILE_DEFINITIONS VERSION="0.1")

set_source_files_properties(main.c DIRECTORY b
    PROPERTIES COMPILE_DEFINITIONS VERSION="0.2")