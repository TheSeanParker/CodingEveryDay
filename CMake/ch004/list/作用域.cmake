function(append list_var)
    list(APPEND ${list_var} d) # 向列表变量中追加元素d
    message("${${list_var}}") # 输出：a;b;c;d
endfunction()

function(append2 list_var)
    list(APPEND ${list_var} d) # 向列表变量中追加元素d
    set(${list_var} ${${list_var}} PARENT_SCOPE)
    message("${${list_var}}") # 输出：a;b;c;d
endfunction()

set(x "a;b;c")
append(x)
message("${x}") # 输出：a;b;c

append2(x)
message("${x}") # 输出：a;b;c;d