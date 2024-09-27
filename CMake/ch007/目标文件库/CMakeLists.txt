cmake_minimum_required(VERSION 3.20)

project(myObjLib)

add_library(myObjLib OBJECT a.c b.c)
add_executable(main main.c $<TARGET_OBJECTS:myObjLib>)