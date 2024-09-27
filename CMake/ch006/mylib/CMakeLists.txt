cmake_minimum_required(VERSION 3.20)

# 定义项目名称和版本
project(mylib VERSION 1.0.0)

# 添加静态库目标mylib，其源代码包含lib.c
add_library(mylib STATIC lib.c)

# 安装mylib构建目标
install(TARGETS mylib)

# 打包
set(CPACK_PACKAGE_NAME "mylib")
include(CPack)