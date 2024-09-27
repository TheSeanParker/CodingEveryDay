set(json [=[{
    "a": {
        "x": 0,
        "y": {}
    },
    "b": [0, 1, 2, 3, 4],
    "c": "cmake"
}]=])

string(JSON res LENGTH ${json})
message("${res}") # 输出：3

string(JSON res LENGTH ${json} a)
message("${res}") # 输出：2

string(JSON res LENGTH ${json} b)
message("${res}") # 输出：5

string(JSON res LENGTH ${json} c) 
# 致命错误：string sub-command JSON LENGTH needs to be called with an element of type ARRAY or OBJECT, got STRING.