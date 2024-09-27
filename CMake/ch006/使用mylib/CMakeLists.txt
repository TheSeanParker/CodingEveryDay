cmake_minimum_required(VERSION 3.20)

# 定义项目名称
project(use_mylib VERSION 1.0.0)

# 在默认搜索目录的"mylib 1.0.0/lib"子目录中查找mylib库
# 将目录路径存入mylib_LIBRARY变量中
find_library(mylib_LIBRARY 
    mylib 
    PATH_SUFFIXES "mylib 1.0.0/lib"
)

# 输出 "C:/Program Files/mylib 1.0.0/lib/mylib.lib"
message("${mylib_LIBRARY}")

# 添加可执行文件目标main，其源代码包含main.c
add_executable(main main.c)

# 链接mylib库到main程序
target_link_libraries(main ${mylib_LIBRARY})