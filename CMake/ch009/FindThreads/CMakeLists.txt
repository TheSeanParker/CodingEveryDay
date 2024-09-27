cmake_minimum_required(VERSION 3.20)
project(find-threads)

# 调用FindThreads模块，它会创建一个导入目标Threads::Threads
find_package(Threads) 

add_executable(main main.cpp)
# 如果不链接Threads::Threads，在Linux环境中构建会出错：
# undefined reference to `pthread_create'
target_link_libraries(main PRIVATE Threads::Threads)