cmake_minimum_required(VERSION 3.20)

set(A FALSE)
set(B "A")

if(B)
    message("B为真")
endif()

if(${B})
else()
    message("\${B}为假")
endif()

while(NOT ${B})
    message("NOT \${B}为真")
    break()
endwhile()