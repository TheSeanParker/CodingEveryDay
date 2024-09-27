file(DOWNLOAD www.example.com download.txt STATUS status)
file(READ download.txt res LIMIT 64)
message("${status}") # 输出：0;"No error"
message("${res}")
# 输出：
# <!doctype html>
# <html>
# <head>
#     <title>Example Domain</title>

file(DOWNLOAD www.example.com/不存在.txt STATUS status)
message("${status}")
# 输出：22;"HTTP response code said error"