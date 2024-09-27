cmake_minimum_required(VERSION 3.20)

project(延迟调用)

cmake_language(DEFER CALL message 结束)

message("----程序开始----")
add_subdirectory(子目录)

cmake_language(DEFER GET_CALL_IDS ids)
message("当前目录的延迟调用ID: ${ids}")

cmake_language(DEFER GET_CALL 自定义ID cmd)
message("取消调用 自定义ID\n其命令及参数为: ${cmd}")

cmake_language(DEFER CANCEL_CALL 自定义ID)

set(var "再见")
message("----程序结束----")