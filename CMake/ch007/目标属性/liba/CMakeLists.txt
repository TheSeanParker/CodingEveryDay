add_library(a STATIC src/liba.c)

# 设置a的目标属性
set_property(TARGET a PROPERTY 
    # 构建要求：将include加入头文件搜索目录
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 设置a的目标属性
set_property(TARGET a PROPERTY 
    # 使用要求：将include加入（引用者的）头文件搜索目录
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)