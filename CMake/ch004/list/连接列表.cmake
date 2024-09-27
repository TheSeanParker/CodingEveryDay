set(x a;b;c)
list(JOIN x "-" res)
message("${res}") # 输出：a-b-c

string(JOIN "-" res ${x})
message("${res}") # 输出：a-b-c