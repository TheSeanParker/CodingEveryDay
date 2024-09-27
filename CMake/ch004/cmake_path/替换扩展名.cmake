set(path "/a/b.x.txt")
cmake_path(REPLACE_EXTENSION path c)
message("${path}") # 输出：/a/b.c

set(path "/a/b.x.txt")
cmake_path(REPLACE_EXTENSION path LAST_ONLY c OUTPUT_VARIABLE res)
message("${res}") # 输出：/a/b.x.c

set(path "/a/.b")
cmake_path(REPLACE_EXTENSION path c OUTPUT_VARIABLE res)
message("${res}") # 输出：/a/.b.c