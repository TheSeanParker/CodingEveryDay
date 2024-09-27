# 将a、b、c组成的部分替换为-
string(REGEX REPLACE "[abc]+" "-" res adabc dccc)
message("${res}") # 输出：-d-d-

# 将由a、b、c组成的部分用括号括起
string(REGEX REPLACE "[abc]+" "(\\0)" res adabc dccc)
message("${res}") # 输出：(a)d(abc)d(ccc)

# 将长度至少为2的由a、b、c组成的部分的第一个字母用括号括起
string(REGEX REPLACE "([abc])([abc]+)" [[(\1)\2]] res adabcdccc)
message("${res}") # 输出：ad(a)bcd(c)cc