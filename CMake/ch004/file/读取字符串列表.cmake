file(STRINGS list.txt res)
message("${res}") # 输出：abc;;CMake;abc;123

file(STRINGS list.txt res ENCODING UTF-8)
message("${res}") # 输出：abc;你好;CMake;abc;123

file(STRINGS list.txt res ENCODING UTF-8 REGEX [a-z]+)
message("${res}") # 输出：abc;CMake;abc

file(STRINGS list.txt res NEWLINE_CONSUME ENCODING UTF-8)
message("${res}")
# 输出：
# abc
# 你好
# CMake
# abc
# 123