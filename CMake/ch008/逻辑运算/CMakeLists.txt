cmake_minimum_required(VERSION 3.20)

project(logical_calc)

add_custom_target(debug-gen-exp ALL
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<BOOL:ABC>" # 输出：1
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<BOOL:NO>" # 输出：0
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<NOT:$<BOOL:NO>>" # 输出：1
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<AND:$<BOOL:A>,$<BOOL:X-NOTFOUND>>" # 输出：0
    COMMAND ${CMAKE_COMMAND} -E echo 
        "$<OR:$<BOOL:A>,$<BOOL:X-NOTFOUND>>" # 输出：1
)