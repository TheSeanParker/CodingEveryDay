cmake_minimum_required(VERSION 3.20)

project(genex_eval)

add_executable(main main.c)

# 设置main的自定义目标属性CUSTOM_EXP的值
set_property(TARGET main PROPERTY CUSTOM_EXP "$<CONFIG>")

add_custom_target(debug-gen-exp ALL
    COMMAND ${CMAKE_COMMAND} -E echo # 输出Debug或Release等
    "$<GENEX_EVAL:$<TARGET_PROPERTY:main,CUSTOM_EXP>>" 
)