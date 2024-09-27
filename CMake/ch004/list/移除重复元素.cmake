set(x a a a b b c d c)

list(REMOVE_DUPLICATES x)
message("${x}") # 输出：a;b;c;d