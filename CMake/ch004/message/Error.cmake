message(SEND_ERROR "错误1")
# CMake Error at 01.Error.cmake:1 (message):
#   错误1
message(FATAL_ERROR "错误2")
# CMake Error at 01.Error.cmake:2 (message):
#   错误2
message("这句消息不会被输出")