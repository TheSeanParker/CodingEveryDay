include(模板定义.cmake)

set(a "a的值")
set(b "b的值")
set(C "C的值")
set(D "D的值")
set(E "E的值")
set(F "F的值")

string(CONFIGURE ${template} res)
message("${res}")