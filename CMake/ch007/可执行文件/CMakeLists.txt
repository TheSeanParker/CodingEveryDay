cmake_minimum_required(VERSION 3.20)

project(myProgram)

add_executable(myProgram main.c)

add_executable(myProgramExcludedFromAll 
    EXCLUDE_FROM_ALL
    main.c
)