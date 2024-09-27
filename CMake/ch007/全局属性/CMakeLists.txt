cmake_minimum_required(VERSION 3.20)

project(global_property)

get_cmake_property(res GENERATOR_IS_MULTI_CONFIG)
message("GENERATOR_IS_MULTI_CONFIG: ${res}")

get_property(res GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG SET)
message("GENERATOR_IS_MULTI_CONFIG is SET: ${res}")