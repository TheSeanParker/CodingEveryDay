cmake_minimum_required(VERSION 3.20)

project(compile_lang)

add_executable(main a.c b.cpp main.c)
target_compile_definitions(main PRIVATE
    $<$<COMPILE_LANGUAGE:C>:A=1>
    $<$<COMPILE_LANGUAGE:CXX>:A=10>
)