set(x a;b;c;D;e)

# 字典序升序，大小写敏感
list(SORT x)
message("${x}") # 输出：D;a;b;c;e

# 字典序升序，大小写不敏感
list(SORT x CASE INSENSITIVE) 
message("${x}") # 输出：a;b;c;D;e

set(x 1 10 2 3 100 4 5)

# 字典序降序，大小写敏感
list(SORT x ORDER DESCENDING)
message("${x}") # 输出：5;4;3;2;100;10;1

# 自然序降序，大小写敏感
list(SORT x COMPARE NATURAL ORDER DESCENDING)
message("${x}") # 输出：100;10;5;4;3;2;1

# 自然序升序，大小写敏感
set(x a2 a10)
list(SORT x COMPARE NATURAL)
message("${x}") # 输出：a2;a10

# 自然序升序，大小写敏感
set(x aa2 a10)
list(SORT x COMPARE NATURAL)
message("${x}") # 输出：a10;aa2

# 文件名升序，大小写敏感
set(x "a/a/c.txt" "a/b.txt" "a/b.pdf")
list(SORT x COMPARE FILE_BASENAME)
message("${x}") # 输出：a/b.pdf;a/b.txt;a/a/c.txt