# 因为CMake在不同平台的安装路径不同，此处在输出中略去了其绝对路径
separate_arguments(out WINDOWS_COMMAND PROGRAM "cmake -P a.cmake")
message("${out}") # 输出：.../cmake.exe; -P a.cmake

separate_arguments(out WINDOWS_COMMAND PROGRAM 
    SEPARATE_ARGS "cmake -P a.cmake")
message("${out}") # 输出：.../cmake.exe;-P;a.cmake