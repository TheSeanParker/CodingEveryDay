
function(f0)
    list(APPEND CMAKE_MESSAGE_CONTEXT "f0")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    message(STATUS "f0被调用")
endfunction()

function(f1)
    list(APPEND CMAKE_MESSAGE_CONTEXT "f1")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    message(STATUS "f1被调用")
    f0()
endfunction()

list(APPEND CMAKE_MESSAGE_CONTEXT "主程序")
f0()
f1()