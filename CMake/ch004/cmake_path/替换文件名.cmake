set(path "/a/b")
cmake_path(REPLACE_FILENAME path x)
message("${path}") # 输出：/a/x

set(path "/a/")
cmake_path(REPLACE_FILENAME path x)
message("${path}") # 输出：/a/