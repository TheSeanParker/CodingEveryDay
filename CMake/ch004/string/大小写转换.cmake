string(TOLOWER "ABCdef" res)
message("${res}") # 输出：abcdef

string(TOUPPER "ABCdef" res)
message("${res}") # 输出：ABCDEF