set(a 1)

if(DEFINED a)
    message("DEFINED a为真")
endif()

if(CACHE{b})
else()
    message("CACHE{b}为假")
endif()

if(COMMAND set)
    message("COMMAND set为真")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/逻辑运算.cmake")
    message("EXISTS \"${CMAKE_CURRENT_LIST_DIR}/逻辑运算.cmake\"为真")
endif()