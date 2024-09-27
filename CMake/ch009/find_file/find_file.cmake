if(WIN32)
    find_file(notepad_path notepad.exe)
    message("${notepad_path}") # 输出：C:/Windows/System32/notepad.exe
endif()

# 使用tree .查看当前目录的树形结构
# ├── a
# │   └── b
# │       └── 1.txt     
# ├── b
# │   └── a
# │       └── 1.txt     
# └── find_file.cmake   

find_file(res1 1.txt HINTS a b PATH_SUFFIXES b)
message("${res1}") # 输出：.../CMake-Book/src/ch009/find_file/a/b/1.txt

find_file(res2 1.txt HINTS a b PATH_SUFFIXES a)
message("${res2}") # 输出：.../CMake-Book/src/ch009/find_file/b/a/1.txt