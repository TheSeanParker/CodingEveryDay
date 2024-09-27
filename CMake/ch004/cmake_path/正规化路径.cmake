set(path "/a/../b/./c")
cmake_path(NORMAL_PATH path)
message("${path}") # 输出：/b/c