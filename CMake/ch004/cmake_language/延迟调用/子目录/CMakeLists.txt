message("----子目录程序开始----")

# 注意这里的延迟调用都是定义在上级目录的
cmake_language(DEFER
    DIRECTORY ..
    ID_VAR id1
    CALL message "结束2: ${var}"
)
cmake_language(DEFER 
    DIRECTORY ..
    ID 自定义ID
    ID_VAR id2
    CALL message 结束3
)

message("id1: ${id1}")
message("id2: ${id2}")

message("----子目录程序结束----")