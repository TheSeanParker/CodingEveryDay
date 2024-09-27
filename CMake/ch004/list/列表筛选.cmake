set(x a1 b2 c0 d e f 1 2 3)
set(y ${x})

list(FILTER x INCLUDE REGEX "^[a-z]$")
message("${x}") # 输出：d;e;f

list(FILTER y EXCLUDE REGEX "^[a-z][0-9]?$")
message("${y}") # 输出：1;2;3