cmake_minimum_required(VERSION 3.20)

if(NOT OFF)
    message("NOT OFF为真")
endif()

if(ON AND YES)
    message("ON AND YES为真")
endif()

if(TRUE AND NOTFOUND)
else()
    message("TRUE AND NOTFOUND为假")
endif()

if(A-NOTFOUND OR YES)
    message("A-NOTFOUND OR YES为真")
endif()