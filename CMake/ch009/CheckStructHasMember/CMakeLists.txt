cmake_minimum_required(VERSION 3.20)
project(check-struct-member)
include(CheckStructHasMember)

check_struct_has_member("std::pair<int,int>" "first" "utility" res 
    LANGUAGE CXX) # 输出：
# -- Performing Test res
# -- Performing Test res - Success