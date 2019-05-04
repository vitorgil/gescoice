cmake_minimum_required(VERSION 3.10)

set (CMAKE_PREFIX_PATH "C:/Qt/5.12.3/mingw73_64/lib/cmake/Qt5")
# set (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ";C:/googletest-distribution/lib/cmake/GTest")
set (GTEST_ROOT "C:/googletest-distribution")

add_subdirectory(src)
#add_subdirectory(test)
