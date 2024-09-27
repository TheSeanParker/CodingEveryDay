# 请先使用NMake生成 ch001/动态库 项目

set(dll_dir "${CMAKE_CURRENT_LIST_DIR}/../../ch001/动态库/")

file(GET_RUNTIME_DEPENDENCIES
    RESOLVED_DEPENDENCIES_VAR resolved
    UNRESOLVED_DEPENDENCIES_VAR unresolved
    EXECUTABLES ${dll_dir}/main.exe
    PRE_EXCLUDE_REGEXES kernel32.dll
)

message("${resolved}")
# 输出：C:/CMake-Book/src/ch004/file/../../ch001/动态库/liba.dll
message("${unresolved}")
# 输出空