cmake_minimum_required(VERSION 3.20)

set("a?b" "变量a?b")

# \? 转义为 ?
message(${a\?b})
message(今天是几号\?) 

# \n 转义为换行符，\t 转义为制表符，\! 转义为 !
message(回答：\n\t今天是1号\!)

set("a;b" "变量a;b")

# 非引号参数中 \; 转义为 ;，且不分隔变量
message(x;y\;z)
# 引号参数中 \; 不转义
message("x;y\;z")
# 变量引用中 \; 转义为 ;
message("${a\;b}")
