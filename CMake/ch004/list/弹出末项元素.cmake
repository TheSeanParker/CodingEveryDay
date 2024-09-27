set(x a b c d e)

list(POP_BACK x)
message("${x}") # 输出：a;b;c;d

list(POP_BACK x x0 x1)
message("${x}") # 输出：a;b
message("${x0}, ${x1}") # 输出：d, c