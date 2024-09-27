string(REPLACE a b res aba)
message("${res}") # 输出：bbb

string(REPLACE a b res abc cab)
message("${res}") # 输出：bbccbb
