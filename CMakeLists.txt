cmake_minimum_required(VERSION 3.10)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")

add_subdirectory(src)
add_subdirectory(test)
