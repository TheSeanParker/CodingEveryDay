execute_process(
    COMMAND ${CMAKE_COMMAND} -Dtext=hello -P 输出变量.cmake
    COMMAND ${CMAKE_COMMAND} -Dtext=world -P 输出变量.cmake
    ERROR_FILE out.txt
)
# out.txt文件的内容如下：
# world
# hello