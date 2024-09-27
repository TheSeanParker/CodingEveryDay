cmake_minimum_required(VERSION 3.20)
project(num_recognizer)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
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

find_package(onnxruntime 1.10 REQUIRED) # 指定依赖的最小版本
find_package(libpng REQUIRED)

add_library(num_recognizer SHARED src/num_recognizer.cpp)

include(GenerateExportHeader)
generate_export_header(num_recognizer)
set_target_properties(num_recognizer PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
)

target_include_directories(num_recognizer PUBLIC include ${CMAKE_BINARY_DIR})
target_link_libraries(num_recognizer PRIVATE onnxruntime::onnxruntime png_shared)
target_compile_definitions(num_recognizer PRIVATE ORT_NO_EXCEPTIONS num_recognizer_EXPORTS)

add_executable(recognize cli/recognize.c)
target_link_libraries(recognize PRIVATE num_recognizer)