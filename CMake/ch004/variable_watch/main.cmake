function(callback var access value filename stack)
    message("${access}访问变量${var}，其值为${value}")
    message("文件路径：${filename}")
    foreach(item ${stack})
        message("    ${item}")
    endforeach()
    message("---")
endfunction()

variable_watch(A callback)
variable_watch(B)

# 访问B变量，触发默认回调，输出变量信息
set(B "${B}")

# 访问A变量，触发自定义回调命令callback
set(A "1")
list(APPEND A "2")
unset(A)

# 在引用的程序中访问A变量，注意观察输出的调用栈
include(b.cmake)