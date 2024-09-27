if(ABC)
else()
    message("ABC不是一个已定义的变量，因此条件为假")
endif()

set(a "XYZ")
set(b "0")
set(c "a-NOTFOUND")

if(a)
    message("a是一个变量，其值非假值常量，因此条件为真")
endif()

if(b)
else()
    message("b是一个变量，其值为假值常量，因此条件为假")
endif()

if(c)
else()
    message("c是一个变量，其值为假值常量，因此条件为假")
endif()