# 请先执行 创建归档文件.cmake

file(ARCHIVE_EXTRACT INPUT 归档.7z
     LIST_ONLY
)
# 输出：
# 归档文件/file.txt
# 归档文件/dir/1.txt
# 归档文件/dir/2.txt
# 归档文件/dir/

message("---")

file(ARCHIVE_EXTRACT INPUT 归档.7z
     DESTINATION 提取归档
     PATTERNS */dir/*.txt
     VERBOSE
)
# 输出：
# x 归档文件/dir/1.txt
# x 归档文件/dir/2.txt