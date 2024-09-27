cmake_minimum_required(VERSION 3.20)

project(cache-var)

set(MY_CACHE "MY_CACHE" CACHE STRING "")
set(MY_ADVANCED_CACHE "MY_ADVANCED_CACHE" CACHE STRING "")
mark_as_advanced(MY_ADVANCED_CACHE)