macro(my_macro p)
    message("-- my_macro --")

    if(p)
        message("p为真")
    endif()

    set(i 1)
    message("ARGV i: ${ARGV${i}}")
endmacro()

function(my_func p)
    message("-- my_func --")

    if(p)
        message("p为真")
    endif()

    set(i 1)
    message("ARGV i: ${ARGV${i}}")
endfunction(my_func)

my_macro(ON x)
my_func(ON x)