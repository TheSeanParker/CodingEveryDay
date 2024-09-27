set(path ./a/)
cmake_path(HASH path res)
message("${res}") # 输出：c5a3bfd9b0e89d1d

set(path ./a/b/..)
cmake_path(HASH path res)
message("${res}") # 输出：c5a3bfd9b0e89d1d