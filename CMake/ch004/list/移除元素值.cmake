set(x a a a b b c d c)

list(REMOVE_ITEM x a)
message("${x}") # 输出：b;b;c;d;c

list(REMOVE_ITEM x b c)
message("${x}") # 输出：d