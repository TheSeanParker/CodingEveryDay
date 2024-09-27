set(x a b c d e)

list(REMOVE_AT x 2)
message("${x}") # 输出：a;b;d;e

list(REMOVE_AT x 2 1)
message("${x}") # 输出：a;e