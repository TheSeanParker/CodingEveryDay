function(A)
    include(带卫哨的程序.cmake)
    include(引用带卫哨的程序.cmake)
endfunction()

function(B)
    include(带全局卫哨的程序.cmake)
    include(引用带全局卫哨的程序.cmake)
endfunction()

A()
A()

message("---")

B()
B()