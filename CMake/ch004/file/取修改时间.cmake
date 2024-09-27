file(TIMESTAMP example.txt res)
message("${res}") # 输出：2021-05-10T23:22:13

file(TIMESTAMP example.txt res "%Y年%m月%d日 %H:%M:%S UTC" UTC)
message("${res}") # 输出：2021年05月10日 15:22:13 UTC