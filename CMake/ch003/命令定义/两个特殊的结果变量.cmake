function(my_copy_func)
    set(options OVERWRITE MOVE)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs PATHS)

    cmake_parse_arguments(
        PARSE_ARGV 0
        my 
        "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    message("my_UNPARSED_ARGUMENTS: ${my_UNPARSED_ARGUMENTS}")
    message("my_KEYWORDS_MISSING_VALUES: ${my_KEYWORDS_MISSING_VALUES}")

endfunction()

my_copy_func(COPY "../dir" DESTINATION PATHS)