cmake_minimum_required(VERSION 3.20)
project(check-ipo-supported)
include(CheckIPOSupported)

add_executable(main main.c)

# 强制IPO：若检查失败，则报告致命错误并终止执行
check_ipo_supported() 
set_property(TARGET main PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

# 可选IPO：若检查失败，则输出警告且不启用IPO
check_ipo_supported(RESULT result OUTPUT output)
if(result)
    set_property(TARGET main PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "不支持链接时优化：${output}")
endif()