cmake_minimum_required(VERSION 3.20)

project(alias-target)

add_library(my_liba STATIC "a.cpp")

if(USE_EXTERNAL_LIBA)
    add_library(liba STATIC IMPORTED)
    set_target_properties(liba PROPERTIES IMPORTED_LOCATION "liba.lib")
else()
    add_library(liba ALIAS my_liba)
endif()

add_executable(main "main.cpp")
target_link_libraries(main liba)