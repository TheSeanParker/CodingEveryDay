set(json [=[{
    "a": {
        "b": ["x", "y", "z"],
        "c": true,
        "d": null
    }
}]=])

string(JSON res ERROR_VARIABLE err GET ${json} a b)
message("a.b=${res}") # 输出：a.b=[ "x", "y", "z" ]

string(JSON res ERROR_VARIABLE err GET ${json} a b 1)
message("a.b[1]=${res}") # 输出：a.b[1]=y

string(JSON res ERROR_VARIABLE err GET ${json} a c)
message("a.c=${res}") # 输出：a.c=ON

string(JSON res ERROR_VARIABLE err GET ${json} a d)
message("a.d=${res}") # 输出a.d=

string(JSON res ERROR_VARIABLE err GET ${json} a e)
message("a.e=${res}, ${err}") 
# 输出：a.e=a-e-NOTFOUND, member 'a e' not found

string(JSON res GET ${json} a e) 
# 致命错误：string sub-command JSON member 'a e' not found.