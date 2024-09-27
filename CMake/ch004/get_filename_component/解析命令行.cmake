get_filename_component(cmd "notepad 1.txt 2.txt" 
                       PROGRAM PROGRAM_ARGS args)
message("${cmd}") # 输出：C:/Windows/System32/notepad.exe
message("${args}") # 输出： 1.txt 2.txt