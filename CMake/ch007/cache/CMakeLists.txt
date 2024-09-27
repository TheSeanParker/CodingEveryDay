cmake_minimum_required(VERSION 3.20)

project(cache_entry_property)

set(VERSION "" CACHE STRING "")
set_property(CACHE VERSION PROPERTY STRINGS 1.0 2.0)
