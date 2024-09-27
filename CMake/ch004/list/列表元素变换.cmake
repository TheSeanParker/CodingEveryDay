set(x a b c d e)

# 前插和追加字符串
list(TRANSFORM x PREPEND " (")
list(TRANSFORM x APPEND ") ")
message("${x}") # 输出：(a) ; (b) ; (c) ; (d) ; (e) 

# 转换为大写字母，存入变量y
list(TRANSFORM x TOUPPER OUTPUT_VARIABLE y)
message("${y}") # 输出：(A) ; (B) ; (C) ; (D) ; (E)

# 对x[0], x[2]删除首尾空白符
list(TRANSFORM x STRIP AT 0 2)
message("${x}") # 输出：(a); (b) ;(c); (d) ; (e)

# 从x[1]到x[4]（间隔为2），替换单个字母为两个字母
list(TRANSFORM x REPLACE [a-z] "\\0\\0" FOR 1 4 2)
message("${x}") # 输出：(a); (bb) ;(c); (dd) ; (e)

# 对值存在连续两个字母的元素，追加!
list(TRANSFORM x APPEND "!" REGEX [a-z][a-z])
message("${x}") # 输出：(a); (bb) !;(c); (dd) !; (e)