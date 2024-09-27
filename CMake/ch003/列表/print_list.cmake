function(print_list l)
    string(JOIN " | " res ${${l}})
    message("${res}")
endfunction()