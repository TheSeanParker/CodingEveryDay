set(a A;B)
set(b C D)
set(c "E F")
set(d G;H I)
set(e "")

foreach(x IN LISTS a b c;d;e ITEMS a b c;d;e)
    message("x: ${x}")
endforeach()