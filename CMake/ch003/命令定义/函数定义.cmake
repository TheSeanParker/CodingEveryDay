function(my_func a b)
    set(result "参数a: ${a}, 参数b: ${b}" PARENT_SCOPE)
endfunction()

my_func(x y)
message("${result}") # 输出：参数a: x, 参数b: y

MY_func(A;B)
message("${result}") # 输出：参数a: A, 参数b: B

MY_FUNC(你 好)
message("${result}") # 输出：参数a: 你, 参数b: 好