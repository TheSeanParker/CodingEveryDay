function(abc_f)
    cmake_parse_arguments(abc "A0;A1" "B0;B1" [=[C0;C1]=] ${ARGN})
    
    # 下面是错误的示范
    # cmake_parse_arguments(abc A0 A1 B0 B1 C0 C1 ${ARGN})
    # cmake_parse_arguments(abc A0;A1 B0;B1 C0;C1 ${ARGN})

    message("A0: ${abc_A0}\nA1: ${abc_A1}")
    message("B0: ${abc_B0}\nB1: ${abc_B1}")
    message("C0: ${abc_C0}\nC1: ${abc_C1}")
endfunction()

abc_f(A0 A1 B0 a B1 b C0 x y C1 c d)