string(HEX "ABC" res)
message("${res}") # 输出：414243

string(HEX "JKL" res)
message("${res}") # 输出：4a4b4c

string(HEX "你好" res)
message("${res}") # 输出：e4bda0e5a5bd