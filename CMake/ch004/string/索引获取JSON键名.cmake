set(json [=[{
    "a": {
        "b": 0,
        "c": {}
    },
    "d": {}
}]=])

string(JSON res MEMBER ${json} 0)
message("${res}") # 输出：a

string(JSON res MEMBER ${json} 1)
message("${res}") # 输出d

string(JSON res MEMBER ${json} a 0)
message("${res}") # 输出b

string(JSON res MEMBER ${json} a 1)
message("${res}") # 输出c

string(JSON res MEMBER ${json} a b 0) 
# 致命错误：string sub-command JSON MEMBER needs to be called with an element of type OBJECT, got NUMBER.