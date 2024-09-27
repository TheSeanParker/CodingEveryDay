message("before setenv \$ENV{PATH}: $ENV{PATH}")
set(ENV{PATH}) # 清空
message("after setenv \$ENV{PATH}: $ENV{PATH}")