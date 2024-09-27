cmake_minimum_required(VERSION 3.20)

set(a 10)
set(b "abc")
set(list 1;10;100)

if(11 GREATER a)
    message("11 GREATER a为真")
endif()

if(1 LESS 2)
    message("1 LESS 2为真")
endif()

if(b STRLESS "b")
    message("b LESS \"b\"为真")
endif()

if(1.2.3 VERSION_LESS 1.10.1)
    message("1.2.3 LESS 1.10.1为真")
endif()

if(abc MATCHES a..)
    message("abc MATCHES a..为真")
endif()

if(ab MATCHES a..)
else()
    message("ab MATCHES a..为假")
endif()

if(a IN_LIST list)
    message("a IN_LIST list为真")
endif()