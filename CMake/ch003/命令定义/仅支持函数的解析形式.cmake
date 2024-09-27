function(my_copy_func)
    set(options OVERWRITE MOVE)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs PATHS)

    cmake_parse_arguments(
        PARSE_ARGV 0
        my 
        "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    message("OVERWRITE:\t${my_OVERWRITE}")
    message("MOVE:\t\t${my_MOVE}")
    message("DESTINATION:\t${my_DESTINATION}")
    message("PATHS: \t\t${my_PATHS}")
    message("---")
endfunction()

my_copy_func(DESTINATION "../folder;name" PATHS 1.txt;2.txt)