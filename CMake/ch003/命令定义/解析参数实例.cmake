function(my_copy_func)
    message("ARGN: ${ARGN}")

    set(options OVERWRITE MOVE)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs PATHS)

    cmake_parse_arguments(
        my 
        "${options}" "${oneValueArgs}" "${multiValueArgs}"
        ${ARGN}
    )

    message("OVERWRITE:\t${my_OVERWRITE}")
    message("MOVE:\t\t${my_MOVE}")
    message("DESTINATION:\t${my_DESTINATION}")
    message("PATHS: \t\t${my_PATHS}")
    message("---")
endfunction()

my_copy_func(DESTINATION ".." PATHS "1.txt" "2.txt" OVERWRITE)
my_copy_func(MOVE DESTINATION "../.." PATHS "3.txt" "4.txt")
my_copy_func(DESTINATION "../folder;name" PATHS 1.txt;2.txt)