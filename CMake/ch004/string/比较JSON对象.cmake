string(JSON res EQUAL [[{"b": 0, "a": 1}]] [[{"a": 1, "b": 0}]])
message("${res}") # 输出：ON

string(JSON res EQUAL [[{"b": null, "a": 1}]] [[{"a": 1}]])
message("${res}") # 输出：OFF