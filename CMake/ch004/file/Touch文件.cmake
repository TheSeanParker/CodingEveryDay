file(TOUCH out.txt out2.txt)
file(TOUCH_NOCREATE out3.txt)

# 执行样例：
# > cd CMake-Book/src/ch004/file
# > ls out*.txt
# Mode                 LastWriteTime         Length Name
# ----                 -------------         ------ ----
# -a---           2021/5/16    21:15             14 out.txt
#
# > cmake -P Touch文件.cmake
# > ls out*.txt
# Mode                 LastWriteTime         Length Name
# ----                 -------------         ------ ----
# -a---           2021/5/16    21:23             14 out.txt
# -a---           2021/5/16    21:23              0 out2.txt