cmake_minimum_required(VERSION 3.20)
project(check-prototype-def)
include(CheckPrototypeDefinition)

check_prototype_definition(sinf 
    "float sinf(float a)" "0"
    "math.h" res) # 输出：
# -- Checking prototype sinf for res
# -- Checking prototype sinf for res - True

check_prototype_definition(sinf 
    "double sinf(float a)" "0"
    "math.h" res2) # 输出：
# -- Checking prototype sinf for res2
# -- Checking prototype sinf for res2 - False