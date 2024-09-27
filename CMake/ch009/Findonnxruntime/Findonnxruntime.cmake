#[=======================================================================[.rst:
Findonnxruntime
-------

Finds the onnxruntime library.（查找onnxruntime库）

Imported Targets（导入目标）
^^^^^^^^^^^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found（若查找成功，该模块会创建如下导入目标）:

``onnxruntime::onnxruntime``
  The onnxruntime library（onnxruntime库）

Result Variables（结果变量）
^^^^^^^^^^^^^^^^^^^^^^^^^^

This will define the following variables（该模块会定义如下变量）:

``onnxruntime_FOUND``
  True if the system has the onnxruntime library.（若成功查找onnxruntime库，则为真值）
``onnxruntime_VERSION``
  The version of the onnxruntime library which was found.（查找到的onnxruntime库的版本号）
``onnxruntime_INCLUDE_DIRS``
  Include directories needed to use onnxruntime.（作为使用要求的onnxruntime的头文件目录）
``onnxruntime_LIBRARIES``
  Libraries needed to link to onnxruntime.（作为使用要求的onnxruntime的链接库文件路径）

Cache Variables（缓存变量）
^^^^^^^^^^^^^^^^^^^^^^^^^

The following cache variables may also be set（该模块会定义如下缓存变量）:

``onnxruntime_INCLUDE_DIR``
  The directory containing ``onnxruntime_c_api.h``.（``onnxruntime_c_api.h``所在目录）
``onnxruntime_LIBRARY``
  The path to the onnxruntime library.（onnxruntime库文件的路径）

Hints（作为提示的查找条件变量）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``onnxruntime_ROOT`` 
  The environment variable that points to the root directory of onnxruntime.（指向onnxruntime安装根目录的环境变量）
#]=======================================================================]

find_path(onnxruntime_INCLUDE_DIR onnxruntime_c_api.h
  HINTS ENV onnxruntime_ROOT
  PATH_SUFFIXES include)

find_library(onnxruntime_LIBRARY
  NAMES onnxruntime
  HINTS ENV onnxruntime_ROOT
  PATH_SUFFIXES lib)

find_file(onnxruntime_VERSION_FILE VERSION_NUMBER
  HINTS ENV onnxruntime_ROOT)

if(onnxruntime_VERSION_FILE)
  file(STRINGS ${onnxruntime_VERSION_FILE} onnxruntime_VERSION LIMIT_COUNT 1)
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(onnxruntime 
  REQUIRED_VARS onnxruntime_LIBRARY onnxruntime_INCLUDE_DIR 
  VERSION_VAR onnxruntime_VERSION
  HANDLE_VERSION_RANGE)

if(onnxruntime_FOUND)
  set(onnxruntime_INCLUDE_DIRS ${onnxruntime_INCLUDE_DIR})
  set(onnxruntime_LIBRARIES ${onnxruntime_LIBRARY})

  add_library(onnxruntime::onnxruntime SHARED IMPORTED)
  target_include_directories(onnxruntime::onnxruntime INTERFACE ${onnxruntime_INCLUDE_DIRS})
  if(WIN32)
    set_target_properties(onnxruntime::onnxruntime PROPERTIES 
      IMPORTED_IMPLIB "${onnxruntime_LIBRARY}")
  else()
    set_target_properties(onnxruntime::onnxruntime PROPERTIES 
      IMPORTED_LOCATION "${onnxruntime_LIBRARY}")
  endif()
endif()