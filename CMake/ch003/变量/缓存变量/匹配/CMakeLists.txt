cmake_minimum_required(VERSION 3.20)
project(MatchOrder)

set(a 缓存变量 CACHE STRING "")
set(a 普通变量)

message("\${a}: ${a}")
message("\$CACHE{a}: $CACHE{a}")