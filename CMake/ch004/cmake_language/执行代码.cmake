set(a TRUE)

cmake_language(EVAL CODE "
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
") # 输出：
# TRUE
# FALSE