string(TIMESTAMP res "%Y/%m/%d %H时%M分%S秒")
message("${res}") # 输出：2021/02/24 23时15分26秒

string(TIMESTAMP res "%Y年%m月%d日 %H:%M:%S UTC" UTC)
message("${res}") # 输出：2021年02月24日 15:15:26 UTC