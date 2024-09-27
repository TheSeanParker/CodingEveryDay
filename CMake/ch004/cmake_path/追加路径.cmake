cmake_path(APPEND res a b c)
message("${res}") # 输出：a/b/c

cmake_path(APPEND_STRING res a b c)
message("${res}") # 输出：a/b/cabc

cmake_path(APPEND res d e)
message("${res}") # 输出：a/b/cabc/d/e

if(WIN32)
    cmake_path(APPEND res a c:b c:c OUTPUT_VARIABLE res2)
else()
    cmake_path(APPEND res a /b c OUTPUT_VARIABLE res2)
endif()

message("${res2}")
# 在Windows操作系统中输出：c:b/c
# 在类Unix操作系统中输出：/b/c