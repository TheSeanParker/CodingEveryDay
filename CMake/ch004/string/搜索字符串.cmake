string(FIND aba a res)
message("${res}") # 输出：0

string(FIND aba a res REVERSE)
message("${res}") # 输出：2

string(FIND aba c res)
message("${res}") # 输出：-1