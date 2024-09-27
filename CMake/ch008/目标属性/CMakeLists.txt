cmake_minimum_required(VERSION 3.20)

project(target-prop)

add_executable(main main.c)
set_target_properties(main PROPERTIES A 1)
target_compile_definitions(main PRIVATE 
    A=$<TARGET_PROPERTY:A> # 等价于 A=$<TARGET_PROPERTY:main,A>
)

add_library(lib dummy.c)
set_target_properties(lib PROPERTIES A 2)
target_compile_definitions(lib PUBLIC
    B=$<TARGET_PROPERTY:A>
)
target_link_libraries(main PRIVATE lib)