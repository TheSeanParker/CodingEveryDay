function(print_matches)
    message("CMAKE_MATCH_COUNT: ${CMAKE_MATCH_COUNT}")
    message("CMAKE_MATCH_0: ${CMAKE_MATCH_0}")
    message("CMAKE_MATCH_1: ${CMAKE_MATCH_1}")
    message("CMAKE_MATCH_2: ${CMAKE_MATCH_2}")
    message("---")
endfunction()

set(regex "([abc])([abc]+)")

# 单次正则匹配
string(REGEX MATCH ${regex} res aaa d abc)
print_matches()
# 输出：
# CMAKE_MATCH_COUNT: 2
# CMAKE_MATCH_0: aaa
# CMAKE_MATCH_1: a
# CMAKE_MATCH_2: aa
# ---

# 全部正则匹配
string(REGEX MATCHALL ${regex} res aaa d abc)
print_matches()
# 输出：
# CMAKE_MATCH_COUNT: 2
# CMAKE_MATCH_0: abc
# CMAKE_MATCH_1: a
# CMAKE_MATCH_2: bc
# ---

# 正则替换
string(REGEX REPLACE ${regex} [[(\1)\2]] res aaa d abc)
print_matches()
# 输出：
# CMAKE_MATCH_COUNT: 2
# CMAKE_MATCH_0: abc
# CMAKE_MATCH_1: a
# CMAKE_MATCH_2: bc
# ---

# 字符串匹配条件判断
if("aaadabc" MATCHES ${regex})
    print_matches()
    # 输出：
    # CMAKE_MATCH_COUNT: 2
    # CMAKE_MATCH_0: aaa
    # CMAKE_MATCH_1: a
    # CMAKE_MATCH_2: aa
    # ---
endif()