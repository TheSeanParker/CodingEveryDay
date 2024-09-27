cmake_minimum_required(VERSION 3.20)

set(on "OFF")

if(on)
    message("ON")
else()
    message("OFF")
endif()

if(${on})
    message("ON")
else()
    message("OFF")
endif()