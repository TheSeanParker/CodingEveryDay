set(regex "([abc]+)")

string(REGEX MATCHALL ${regex} res adb dcd abcdcba)
message("${res}") # 输出：a;b;c;abc;cba