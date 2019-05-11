cmake_minimum_required(VERSION 3.10)

if (WIN32)
  set (CMAKE_PREFIX_PATH "C:/Qt/5.12.3/mingw73_64/lib/cmake/Qt5")
  set (GTEST_ROOT "C:/googletest-distribution")
endif()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")

add_subdirectory(src)
add_subdirectory(test)
