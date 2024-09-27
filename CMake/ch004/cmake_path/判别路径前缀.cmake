set(path "/a/b/c")
cmake_path(IS_PREFIX path "/a/b/c/d" res0) # ON
cmake_path(IS_PREFIX path "/a/b/c" res1) # ON
cmake_path(IS_PREFIX path "/a/b" res2) # OFF
cmake_path(IS_PREFIX path "/a/b/cd" res3) # OFF
message("${res0} ${res1} ${res2} ${res3}") # 输出：ON ON OFF OFF

set(path "/a/b/..")
cmake_path(IS_PREFIX path "/a/b" res0) # OFF
cmake_path(IS_PREFIX path "/a/b" NORMALIZE res1) # ON
message("${res0} ${res1}") # 输出：OFF ON

set(path "/a/b/c")
cmake_path(IS_PREFIX path "/a/c/../b/c/d" res0) # OFF
cmake_path(IS_PREFIX path "/a/c/../b/c/d" NORMALIZE res1) # ON
message("${res0} ${res1}") # 输出：OFF ON