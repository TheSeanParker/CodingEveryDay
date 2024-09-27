cmake_minimum_required(VERSION 3.20)

set(A "NOT A")
set(B "A")

if(${B} STREQUAL "A")
else()
    message("\${B} STREQUAL \"A\"为假")
endif()

if("${B}" STREQUAL "A")
    message("\"\${B}\" STREQUAL \"A\"为真")
endif()