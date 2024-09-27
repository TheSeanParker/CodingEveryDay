# 数列划分
# 
# arr: 数列
# pivot: 基准值
# left: 划分后的子数列变量名（比基准值小的部分）
# right: 划分后的子数列变量名（比基准值大的部分）
function(partition arr pivot left right)
    # 遍历数列
    foreach(x ${arr})
        # 根据当前值与基准值的比较结果，分别将当前值追加到不同的子数列中
        if(${x} LESS ${pivot})
            list(APPEND _left ${x})
        else()
            list(APPEND _right ${x})
        endif()
    endforeach()

    # 将两个子数列定义到上层作用域的变量中
    set(${left} ${_left} PARENT_SCOPE)
    set(${right} ${_right} PARENT_SCOPE)
endfunction()

# 快速排序
# 
# input: 输入数列
# res: 存放排序结果的数列变量名
function(quick_sort input res)
    # 取数列长度
    list(LENGTH input input_len)

    # 若数列长度小于等于1，则无需排序，直接设置结果
    if(${input_len} LESS_EQUAL 1)
        set(${res} "${input}" PARENT_SCOPE)
        return()
    endif()

    # 取数列第一个元素作为基准值
    list(GET input 0 pivot)
    # 将基准值从数列中删掉，即从第2个元素开始取子数列
    list(SUBLIST input 1 -1 input)

    # 划分出两部分子数列
    partition("${input}" ${pivot} left right)
    # 递归调用自身，对两个子数列进行快速排序
    quick_sort("${left}" left)
    quick_sort("${right}" right)

    # 将比基准值小的子数列、基准值、比基准值大的子数列连接起来
    list(APPEND _res ${left} ${pivot} ${right})
    # 设置到上层作用域的结果变量中
    set(${res} "${_res}" PARENT_SCOPE)
endfunction()

# 接受命令行输入的参数
# 从第4个参数开始，因为要忽略以下前4个参数：
# "cmake" "-P" "快速排序.cmake" "--"
foreach(i RANGE 4 ${CMAKE_ARGC})
    list(APPEND input ${CMAKE_ARGV${i}})
endforeach()

message("排序前：${input}")
quick_sort("${input}" res)
message("排序后：${res}")