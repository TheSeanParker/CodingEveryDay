string(JOIN "-" res 2021 02 21)
message("${res}") # 输出：2021-02-21

string(JOIN "->" res A B C)
message("${res}") # 输出：A->B->C