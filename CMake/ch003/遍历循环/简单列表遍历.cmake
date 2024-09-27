foreach(x A;B;C D E F)
    message("x: ${x}")
endforeach()

message("---")

set(list X;Y;Z)
foreach(x ${list})
    message("x: ${x}")
endforeach()