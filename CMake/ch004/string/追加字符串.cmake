set(res "你好")
string(APPEND res "，" "CMake" "！")
message("${res}") # 输出：你好，CMake！