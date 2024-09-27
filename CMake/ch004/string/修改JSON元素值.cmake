set(json [=[{
    "a": {
        "b": 0,
        "c": {}
    },
    "d": {}
}]=])

string(JSON res SET ${json} a c "\"a.c的新值\"")
message("设置a.c:\n${res}")
# {
#   "a" :
#   {
#     "b" : 0,
#     "c" : "a.c的新值"
#   },
#   "d" : {}
# }

string(JSON res SET ${json} d "[1, 2, 3]")
message("设置d:\n${res}")
# {
#   "a" :
#   {
#     "b" : 0,
#     "c" : {}
#   },
#   "d" : [ 1, 2, 3 ]
# }

string(JSON res SET ${json} a b "a.b的新值") # 致命错误
