cmake_minimum_required(VERSION 3.20)
project(check-source-compiles)
include(CheckSourceCompiles)

check_source_compiles(C "int main() { return 0; }" res) # 输出：
# -- Performing Test res
# -- Performing Test res - Success
message("${res}") # 输出：1

set(CMAKE_REQUIRED_QUIET True)
check_source_compiles(C "invalid code" res2) # 输出：
# -- Performing Test res2
# -- Performing Test res2 - Failed
message("${res2}") # 输出空值