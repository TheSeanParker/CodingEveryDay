cmake_minimum_required(VERSION 3.20)
project(Notepad)

set(path_to_notepad "" CACHE FILEPATH "Path to notepad.exe")

# 下面的命令将会用记事本打开同一目录中的in.txt
execute_process(COMMAND "cmd" "/c" 
    ${path_to_notepad} ${CMAKE_CURRENT_LIST_DIR}/in.txt)