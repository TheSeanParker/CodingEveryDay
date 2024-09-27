file(WRITE out.txt 123)
file(RENAME out.txt rename.txt)
file(READ rename.txt res)
message("${res}") # 输出：123