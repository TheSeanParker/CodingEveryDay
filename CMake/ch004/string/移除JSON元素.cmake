set(json [=[{
    "a": {
        "b": 0,
        "c": {}
    },
    "d": {}
}]=])

string(JSON res REMOVE ${json} a c)
message("删除a.c后:\n${res}")
# {
#   "a" :
#   {
#     "b" : 0
#   },
#   "d" : {}
# }

string(JSON res REMOVE ${json} d)
message("删除d后:\n${res}")
# {
#   "a" :
#   {
#     "b" : 0,
#     "c" : {}
#   }
# }