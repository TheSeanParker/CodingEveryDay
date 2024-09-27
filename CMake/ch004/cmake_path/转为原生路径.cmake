set(path "a/1.txt;b/2.txt")
cmake_path(NATIVE_PATH path res)
message("${res}")
# 在Windows操作系统中输出：a\1.txt;b\2.txt
# 在类Unix操作系统中输出：a/1.txt;b/2.txt

cmake_path(CONVERT "a/1.txt;b/2.txt" TO_NATIVE_PATH_LIST res)
message("${res}")
# 在Windows操作系统中输出：a\1.txt;b\2.txt
# 在类Unix操作系统中输出：a/1.txt:b/2.txt