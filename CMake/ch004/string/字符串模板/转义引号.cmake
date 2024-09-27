cmake_minimum_required(VERSION 3.20)

set(a "a的值，有\"引号\"")

string(CONFIGURE "std::string str = \"@a@\";" res)
message("${res}")

string(CONFIGURE "std::string str = \"@a@\";" res ESCAPE_QUOTES)
message("${res}")