set(regex "[abc]+")

string(REGEX MATCH ${regex} res aaa)
message("${res}") # 输出：aaa

string(REGEX MATCH ${regex} res aaa bbb ccc abc)
message("${res}") # 输出：aaabbbcccabc

string(REGEX MATCH ${regex} res aaad)
message("${res}") # 输出：aaa

string(REGEX MATCH ${regex} res bcd aaa)
message("${res}") # 输出：bc

set(regex ^[abc]+$)

string(REGEX MATCH ${regex} res aaa)
message("${res}") # 输出：aaa

string(REGEX MATCH ${regex} res aaa bbb ccc abc)
message("${res}") # 输出：aaabbbcccabc

string(REGEX MATCH ${regex} res aaad)
message("${res}") # 输出空

string(REGEX MATCH ${regex} res bcd aaa)
message("${res}") # 输出空