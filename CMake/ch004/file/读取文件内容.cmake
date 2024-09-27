file(READ example.txt res)
message("${res}") # 输出：你好，CMake！

file(READ example.txt res LIMIT 6)
message("${res}") # 输出：你好

file(READ example.txt res OFFSET 9)
message("${res}") # 输出：CMake！

file(READ example.txt res OFFSET 9 HEX)
message("${res}") # 输出：434d616b65efbc81