message("准备加锁…")
file(LOCK ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
message("已加锁，等待10秒")
execute_process(COMMAND ${CMAKE_COMMAND} -E sleep 10)
message("锁已释放")