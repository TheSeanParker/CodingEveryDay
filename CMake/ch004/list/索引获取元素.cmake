set(x "a;b;c")

list(GET x 0 res)
message("${res}") # 输出：a

list(GET x 0 2 res)
message("${res}") # 输出：a;c