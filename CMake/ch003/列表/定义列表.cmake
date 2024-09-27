include(print_list.cmake)

set(a "a;b;c")
set(b a;b;c)
set(c a b c)

print_list(a) # 输出：a | b | c
print_list(b) # 输出：a | b | c
print_list(c) # 输出：a | b | c