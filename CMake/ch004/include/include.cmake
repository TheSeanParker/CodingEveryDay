include(外部程序.cmake)
message("a: ${a}")

include(外部程序 OPTIONAL RESULT_VARIABLE out) 
message("include(外部程序): ${out}")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(外部程序 RESULT_VARIABLE out)
message("${out}")