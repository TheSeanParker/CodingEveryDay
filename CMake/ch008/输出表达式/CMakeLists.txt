cmake_minimum_required(VERSION 3.20)

project(output_gen_exp)

# 构建debug-gen-exp自定义目标，以输出当前构建模式
add_custom_target(debug-gen-exp 
    COMMAND ${CMAKE_COMMAND} -E echo "CONFIG: $<CONFIG>"
)