set(path "/a/b.x.txt")
cmake_path(REMOVE_EXTENSION path)
message("${path}") # 输出：/a/b

set(path "/a/b.x.txt")
cmake_path(REMOVE_EXTENSION path LAST_ONLY OUTPUT_VARIABLE res)
message("${res}") # 输出：/a/b.x

set(path "/a/.b")
cmake_path(REMOVE_EXTENSION path LAST_ONLY OUTPUT_VARIABLE res)
message("${res}") # 输出：/a/.b