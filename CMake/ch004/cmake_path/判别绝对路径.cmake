set(a "c:a")
cmake_path(IS_ABSOLUTE a res)
message("${res}") # 输出：OFF

set(b "c:/a")
cmake_path(IS_ABSOLUTE b res)
message("${res}") # 仅在Windows操作系统中输出：ON

set(c "/a")
cmake_path(IS_ABSOLUTE c res)
message("${res}") # 仅在类Unix操作系统中输出：ON