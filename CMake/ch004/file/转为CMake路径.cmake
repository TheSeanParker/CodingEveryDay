if(WIN32)
    file(TO_CMAKE_PATH "a\\1.txt;b/2.txt" res)
else()
    file(TO_CMAKE_PATH "a\\1.txt:b/2.txt" res)
endif()

message("${res}") # 输出：a/1.txt;b/2.txt