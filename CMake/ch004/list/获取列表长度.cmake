set(x "a;b;c;d")
list(LENGTH x res)
message("${res}") # 输出：4

set(x "")
list(LENGTH x res)
message("${res}") # 输出：0