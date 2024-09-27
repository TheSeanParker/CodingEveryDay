function(f mode)
    get_filename_component(res "a/b.c.txt" ${mode})
    message("${res}")
endfunction()

f(DIRECTORY) # 输出：a
f(NAME) # 输出：b.c.txt
f(EXT) # 输出：.c.txt
f(NAME_WE) # 输出：b
f(LAST_EXT) # 输出：.txt
f(NAME_WLE) # 输出：b.c

get_filename_component(res "a/b.c.txt" ABSOLUTE BASE_DIR C:/)
message("${res}") # 输出：C:/a/b.c.txt