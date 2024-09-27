set(cmd [[cmd a 'b' c]]) # 注意这里用了括号参数

separate_arguments(out WINDOWS_COMMAND "${cmd}")
message("{out}") # 输出：cmd;a;'b';c

separate_arguments(out UNIX_COMMAND "${cmd}")
message("${out}") # 输出：cmd;a;b;c