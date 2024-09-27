execute_process(COMMAND ${CMAKE_COMMAND} -E echo "hello\n" 
    OUTPUT_VARIABLE out
)
message("\"${out}\"")
# 输出："hello
# 
# "

execute_process(COMMAND ${CMAKE_COMMAND} -E echo "hello\n " 
    OUTPUT_VARIABLE out 
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("out: \"${out}\"") # 输出："hello"