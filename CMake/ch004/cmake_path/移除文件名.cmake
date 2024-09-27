set(path "/a/b")
cmake_path(REMOVE_FILENAME path)
message("${path}") # 输出：/a/

# path的文件名部分已被移除，下面的命令不会对其进行修改
cmake_path(REMOVE_FILENAME path OUTPUT_VARIABLE res)
message("${res}") # 输出：/a/