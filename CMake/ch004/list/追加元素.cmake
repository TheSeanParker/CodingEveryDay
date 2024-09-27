set(x a;b;c)
list(APPEND x d e)
message("${x}") # 输出：a;b;c;d;e