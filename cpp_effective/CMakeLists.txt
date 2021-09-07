cmake_minimum_required(VERSION 3.8)

add_executable(E24_demo01 E24/demo01.cpp)

include_directories(E25)
add_executable(E25_test E25/test.cpp)
add_executable(E25_test_t E25/test_t.cpp)
