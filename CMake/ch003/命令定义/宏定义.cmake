macro(my_macro a b)
    set(result "参数a: ${a}, 参数b: ${b}")
endmacro()

my_macro(x y)
message("${result}") # 输出：参数a: x, 参数b: y

MY_macro(A;B)
message("${result}") # 输出：参数a: A, 参数b: B

MY_MACRO(你 好)
message("${result}") # 输出：参数a: 你, 参数b: 好