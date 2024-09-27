include(模板定义.cmake)

set(a "a的值")
set(b "b的值")

set(C "ON")
set(D "TRUE")
set(E "1")
set(F "YES")

string(CONFIGURE ${template} res)
message("${res}")