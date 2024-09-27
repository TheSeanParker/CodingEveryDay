set(a "/")
cmake_path(GET a RELATIVE_PART res)
message("${res}") # 输出空
cmake_path(GET a PARENT_PATH res)
message("${res}") # 输出：/

set(b "1.2.3.txt")
cmake_path(GET b EXTENSION res)
message("${res}") # 输出：.2.3.txt
cmake_path(GET b EXTENSION LAST_ONLY res)
message("${res}") # 输出：.txt

set(c "a/b")
cmake_path(GET c FILENAME res)
message("${res}") # 输出：b

set(d "a/b/")
cmake_path(GET d FILENAME res)
message("${res}") # 输出空

set(e "/a/.x.txt")
cmake_path(GET e FILENAME res)
message("${res}") # 输出：.x.txt
cmake_path(GET e STEM res)
message("${res}") # 输出：.x
cmake_path(GET e EXTENSION res)
message("${res}") # 输出：.txt