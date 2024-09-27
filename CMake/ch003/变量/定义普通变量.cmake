function(f)
    set(a "我是修改后的a")
    set(b "我是b")
    set(c "我是c" PARENT_SCOPE)
endfunction()

set(a "我是a")
f()

message("a: ${a}")
message("b: ${b}")
message("c: ${c}")