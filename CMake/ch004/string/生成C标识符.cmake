string(MAKE_C_IDENTIFIER a123! res)
message("${res}") # 输出：a123_

string(MAKE_C_IDENTIFIER 123a! res)
message("${res}") # 输出：_123a_

string(MAKE_C_IDENTIFIER a哈b哈c res)
message("${res}") # 输出：a___b___c