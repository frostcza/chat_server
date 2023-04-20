cmake_minimum_required(VERSION 3.10)
project(muduo_test)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

add_executable(muduo_test muduo_server.cpp)
target_link_libraries(muduo_test muduo_net muduo_base pthread)