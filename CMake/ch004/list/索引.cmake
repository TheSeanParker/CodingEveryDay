set(x "a;b;c")

foreach(i 0 1 2 -1 -2 -3)
    list(GET x ${i} res) # 获取列表变量x中的第i个元素到res
    message("x[${i}] = ${res}")
endforeach()
# 输出：
# x[0] = a
# x[1] = b
# x[2] = c
# x[-1] = c
# x[-2] = b
# x[-3] = a