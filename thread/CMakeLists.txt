cmake_minimum_required(VERSION 2.8.3)
project(thread_mutex)
# add_executable(xianchengDemo xianchengDemo.cpp )
# add_executable(xianchengNojoin xianchengNojoin.cpp )
# add_executable(get_id get_id.cpp )
find_package(PCL REQUIRED)
include_directories(
    ${PCL_INCLUDE_DIRS}
)

# add_executable(get_id_test get_id_test.cpp )
# target_link_libraries(get_id_test ${PCL_LIBRARIES})

# add_executable(${PROJECT_NAME} print_mutex.cpp)
# target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

# add_executable(print_lock_guard print_lock_guard.cpp )
# target_link_libraries(print_lock_guard ${PCL_LIBRARIES})

add_executable(lock_guard lock_guard.cpp )
target_link_libraries(lock_guard ${PCL_LIBRARIES})

