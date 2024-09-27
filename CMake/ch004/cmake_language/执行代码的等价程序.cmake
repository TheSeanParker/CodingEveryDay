set(a TRUE)

file(WRITE temp.cmake "
    if(a)
        message(TRUE)
    else()
        message(FALSE)
    endif()
" "
    if(b)
        message(TRUE)
    else()
        message(FALSE)
    endif()
")

include(temp.cmake)