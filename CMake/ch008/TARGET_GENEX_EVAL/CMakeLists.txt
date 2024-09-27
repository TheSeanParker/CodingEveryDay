cmake_minimum_required(VERSION 3.20)

project(genex_eval)

add_executable(main main.c)
add_executable(main2 MACOSX_BUNDLE main.c)

set_property(TARGET main PROPERTY A "$<TARGET_PROPERTY:A>")
set_property(TARGET main2 PROPERTY A "main2.A")

add_custom_target(debug-gen-exp ALL
    COMMAND ${CMAKE_COMMAND} -E echo # 输出main2.A
    "$<TARGET_GENEX_EVAL:main2,$<TARGET_PROPERTY:main,A>>" 
)