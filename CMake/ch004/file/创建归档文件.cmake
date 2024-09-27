file(ARCHIVE_CREATE OUTPUT 归档.7z
     PATHS 归档文件/file.txt 归档文件/dir
     FORMAT 7zip
     MTIME "2020-01-01"
     VERBOSE
)
# 输出：
# 归档文件/file.txt
# 归档文件/dir
# 归档文件/dir/1.txt
# 归档文件/dir/2.txt