cmake_minimum_required(VERSION 3.20)
project(check-source-runs)
include(CheckSourceRuns)

check_source_runs(C "int main() { return 0; }" res) # 输出：
# -- Performing Test res
# -- Performing Test res - Success
message("${res}") # 输出：1

check_source_runs(C "int main() { return 1; }" res2) # 输出：
# -- Performing Test res2
# -- Performing Test res2 - Failed
message("${res2}") # 输出空值