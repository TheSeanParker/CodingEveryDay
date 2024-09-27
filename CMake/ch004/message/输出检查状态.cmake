message(CHECK_START "寻找依赖库")

    message(CHECK_START "寻找头文件")

    set(HEADER_FOUND True)
    if(HEADER_FOUND)
        message(CHECK_PASS "已找到")
    else()
        message(CHECK_FAIL "未找到")
    endif()

    message(CHECK_START "寻找源文件")

    set(SOURCE_FOUND False)
    if(SOURCE_FOUND)
        message(CHECK_PASS "已找到")
    else()
        message(CHECK_FAIL "未找到")
    endif()

if(HEADER_FOUND AND SOURCE_FOUND)
    message(CHECK_PASS "已找到")
else()
    message(CHECK_FAIL "未找到")
endif()
