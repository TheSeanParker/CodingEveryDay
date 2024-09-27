set(x a b c d e)

list(POP_FRONT x)
message("${x}") # 输出：b;c;d;e

list(POP_FRONT x x0 x1)
message("${x}") # 输出：d;e
message("${x0}, ${x1}") # 输出：b, c