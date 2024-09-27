set(res "！")
string(PREPEND res "您好" "，" "CMake")
message("${res}") # 输出：你好，CMake！