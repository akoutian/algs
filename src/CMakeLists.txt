cmake_minimum_required(VERSION 3.20)

project(algs LANGUAGES CXX)

include(CTest)

include(cmake/compiler-options.cmake)
include(cmake/configuration.cmake)
include(cmake/functions.cmake)
include(cmake/conan-setup.cmake)

add_subdirectory(pq)
add_subdirectory(qs)
add_subdirectory(radix)
add_subdirectory(st)
add_subdirectory(stack)
add_subdirectory(tst)
