# 目录结构如下：
# 遍历路径
# |-- 1.csv
# |-- 1.jpg
# |-- 1.txt
# |-- a
#     |-- 2.txt
#     |-- b
#         |-- 3.txt

file(GLOB_RECURSE res
    RELATIVE "${CMAKE_CURRENT_LIST_DIR}/遍历路径" 
    遍历路径/*)
message("${res}") # 输出：1.csv;1.jpg;1.txt;a/2.txt;a/b/3.txt

file(GLOB_RECURSE res
    RELATIVE "${CMAKE_CURRENT_LIST_DIR}/遍历路径" 
    遍历路径/*.txt)
message("${res}") # 输出：1.txt;a/2.txt;a/b/3.txt

file(GLOB_RECURSE res
    RELATIVE "${CMAKE_CURRENT_LIST_DIR}/遍历路径" 
    遍历路径/*/*.txt)
message("${res}") # 输出：a/2.txt;a/b/3.txt