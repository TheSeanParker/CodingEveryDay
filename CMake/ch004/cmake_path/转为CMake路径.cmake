if(WIN32)
    cmake_path(CONVERT "a\\.\\1.txt;b/2.txt" TO_CMAKE_PATH_LIST res NORMALIZE)
else()
    cmake_path(CONVERT "a\\.\\1.txt:b/2.txt" TO_CMAKE_PATH_LIST res NORMALIZE)
endif()

message("${res}")
# 在Windows操作系统中输出：a/1.txt;b/2.txt
# 在类Unix操作系统中输出：a\.\1.txt;b/2.txt