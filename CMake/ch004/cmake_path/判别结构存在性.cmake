set(a "/")
cmake_path(HAS_ROOT_PATH a res)
message("${res}") # 输出：ON
cmake_path(HAS_PARENT_PATH a res)
message("${res}") # 输出：ON

set(b "1.txt")
cmake_path(HAS_ROOT_PATH b res)
message("${res}") # 输出：OFF
cmake_path(HAS_PARENT_PATH b res)
message("${res}") # 输出：OFF