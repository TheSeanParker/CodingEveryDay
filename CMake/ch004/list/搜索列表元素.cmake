set(x a;b;c;d)

list(FIND x c res)
message("${res}") # 输出：2

list(FIND x e res)
message("${res}") # 输出：-1