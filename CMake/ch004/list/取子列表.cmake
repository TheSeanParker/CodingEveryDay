set(x a b c d)

list(SUBLIST x 1 2 res)
message("${res}") # 输出：b;c

list(SUBLIST x 1 -1 res)
message("${res}") # 输出：b;c;d

list(SUBLIST x 1 10 res)
message("${res}") # 输出：b;c;d