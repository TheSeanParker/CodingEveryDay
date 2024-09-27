string(MD5 res "abc")
message("${res}") # 输出：900150983cd24fb0d6963f7d28e17f72

string(SHA3_224 res "abc")
message("${res}") # 输出：e642824c3f8cf24ad09234ee7d3c766fc9a3a5168d0c94ad73b46fdf