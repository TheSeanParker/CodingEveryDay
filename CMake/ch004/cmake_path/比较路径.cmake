cmake_path(COMPARE "a\\b" EQUAL "a/b" res)
message("${res}") # 输出：ON

cmake_path(COMPARE "a/b" EQUAL "a/b/" res)
message("${res}") # 输出：OFF

cmake_path(COMPARE "a/b" NOT_EQUAL "a/b/c/.." res)
message("${res}") # 输出：ON