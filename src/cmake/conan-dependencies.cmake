cmake_minimum_required(VERSION 3.20)

if(BUILD_TESTING)
  list(APPEND CONAN_BUILD_REQUIRES doctest/2.4.8)
endif()
