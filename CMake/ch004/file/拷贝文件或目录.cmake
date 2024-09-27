file(COPY 拷贝文件 DESTINATION 拷贝目标/1
     FILES_MATCHING
     PATTERN *.txt
)

file(COPY 拷贝文件 DESTINATION 拷贝目标/2
     REGEX /[0-9]+.txt$ EXCLUDE
)

file(COPY 拷贝文件 DESTINATION 拷贝目标/3
     FILES_MATCHING
     PATTERN *.jpg
     REGEX /[0-9].txt$
)