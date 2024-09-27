file(MD5 example.txt res)
message("${res}")
# 输出：5aabb39511b6e04be5d5ca5a2a2e7dbd

file(SHA256 example.txt res)
message("${res}")
# 输出：71de704359376c5f9e83cd3e2e62d29915c4b11fb40d84c2b69529d5f1d5d70d