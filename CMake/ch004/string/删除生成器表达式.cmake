string(GENEX_STRIP "a$<1:b;c>d" res)
message("${res}") # 输出：ad

string(GENEX_STRIP "a;$<1:b;c>;d;$<TARGET_OBJECTS:some_target>" res)
message("${res}") # 输出：a;d