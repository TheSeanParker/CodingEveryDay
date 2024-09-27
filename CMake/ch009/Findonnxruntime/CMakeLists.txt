cmake_minimum_required(VERSION 3.20)
project(find-onnxruntime)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR};${CMAKE_MODULE_PATH}")
set(CMAKE_CXX_STANDARD 11) # 设置C++标准为11
set(onnx_version 1.10.0) # 根据下载的版本进行设置，本例使用1.10.0版本

# 请下载onnxruntime库的压缩包，并解压至该目录中
if("$ENV{onnxruntime_ROOT}" STREQUAL "")
  if(WIN32)
      set(ENV{onnxruntime_ROOT} "${CMAKE_CURRENT_LIST_DIR}/onnxruntime-win-x64-${onnx_version}")
  elseif(APPLE)
      set(ENV{onnxruntime_ROOT} "${CMAKE_CURRENT_LIST_DIR}/onnxruntime-osx-universal2-${onnx_version}")
  else()
      set(ENV{onnxruntime_ROOT} "${CMAKE_CURRENT_LIST_DIR}/onnxruntime-linux-x64-${onnx_version}")
  endif()
endif()

find_package(onnxruntime 1.10) # 指定依赖的最小版本
add_executable(main main.cpp)
target_link_libraries(main onnxruntime::onnxruntime)
target_compile_definitions(main PRIVATE ORT_NO_EXCEPTIONS)