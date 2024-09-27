include(模板定义.cmake)

set(a "a的值")
set(b "b的值")

set(C "OFF")
set(D "FALSE")
set(E "0")
set(F "IGNORE")

string(CONFIGURE ${template} res)
message("${res}")