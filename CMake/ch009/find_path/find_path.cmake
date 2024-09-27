if(WIN32)
    find_path(notepad_path notepad.exe)
    message("${notepad_path}") # 输出：C:/Windows/System32
endif()

# 使用tree .查看当前目录的树形结构
# ├── a
# │   └── b
# │       └── 1.txt     
# ├── b
# │   └── a
# │       └── 1.txt     
# └── find_path.cmake   

find_path(res1 1.txt HINTS a b PATH_SUFFIXES b)
message("${res1}") # 输出：.../CMake-Book/src/ch009/find_path/a/b

find_path(res2 1.txt HINTS a b PATH_SUFFIXES a)
message("${res2}") # 输出：.../CMake-Book/src/ch009/find_path/b/a