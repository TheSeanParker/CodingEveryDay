string(SUBSTRING "abc" 1 1 res)
message(${res}) # 输出：b

string(SUBSTRING "abc" 1 -1 res)
message(${res}) # 输出：bc

string(SUBSTRING "abc" 1 10 res)
message(${res}) # 输出：bc

string(SUBSTRING "你好" 3 3 res)
message(${res}) # 输出：好