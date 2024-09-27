cmake_minimum_required(VERSION 3.20)

if(NOT TRUE AND FALSE OR TRUE)
    message("NOT FALSE AND TRUE OR FALSE为真")
endif()

if(NOT (TRUE AND (FALSE OR TRUE)))
else()
    message("NOT FALSE AND TRUE OR FALSE为假")
endif()