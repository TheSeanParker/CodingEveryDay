#[=======================================================================[.rst:
Findlibpng
-------

Finds the libpng library.（查找libpng库）

Imported Targets（导入目标）
^^^^^^^^^^^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found（若查找成功，该模块会创建如下导入目标）:

``png_shared``
  The libpng shared library（libpng动态库）
``png_static``
  The libpng static library（libpng静态库）

Result Variables（结果变量）
^^^^^^^^^^^^^^^^^^^^^^^^^^

This will define the following variables（该模块会定义如下变量）:

``libpng_FOUND``
  True if the system has the libpng library.（若成功查找libpng库，则为真值）
``libpng_INCLUDE_DIRS``
  Include directories needed to use libpng.（作为使用要求的libpng的头文件目录）
``libpng_LIBRARIES``
  Libraries needed to link to libpng shared library.（作为使用要求的libpng的动态链接库文件路径）

Cache Variables（缓存变量）
^^^^^^^^^^^^^^^^^^^^^^^^^

The following cache variables may also be set（该模块会定义如下缓存变量）:

``libpng_INCLUDE_DIR``
  The directory containing ``png.h``.（``png.h``所在目录）
#]=======================================================================]

# 调用libpng库自带的配置文件来查找软件包，其自带配置文件会创建两个导入库目标：
# 1. 动态库导入目标``png_shared``
# 2. 静态库导入目标``png_static``
find_package(libpng CONFIG CONFIGS libpng16.cmake)

# 若成功查找，为两个库目标补上缺失的头文件目录属性
if(libpng_FOUND)
  # 获取png动态库导入目标对应动态库文件的路径，首先尝试其IMPORTED_LOCATION属性
  get_target_property(libpng_LIBRARY png_shared IMPORTED_LOCATION)
  # 若未能获得动态库文件路径，再尝试其IMPORTED_LOCATION_RELEASE属性
  if(NOT libpng_LIBRARY)
    get_target_property(libpng_LIBRARY png_shared IMPORTED_LOCATION_RELEASE)
  endif()
  # 根据png动态库的路径，设置libpng的根目录
  set(_png_root "${libpng_LIBRARY}/../..")

  # 查找png.h头文件所在目录的路径
  find_path(libpng_INCLUDE_DIR png.h
    HINTS ${_png_root}
    PATH_SUFFIXES include)
  # 为png和png_static导入库目标设置头文件目录属性
  target_include_directories(png_shared INTERFACE ${libpng_INCLUDE_DIR})
  target_include_directories(png_static INTERFACE ${libpng_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)

# 检查变量是否有效以及配置文件是否成功执行
find_package_handle_standard_args(libpng 
  REQUIRED_VARS libpng_LIBRARY libpng_INCLUDE_DIR
  CONFIG_MODE)

# 若一切成功，设置结果变量
if(libpng_FOUND)
  set(libpng_INCLUDE_DIRS ${libpng_INCLUDE_DIR})
  set(libpng_LIBRARIES ${libpng_LIBRARY})
endif()
