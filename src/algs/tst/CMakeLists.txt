add_library(tst INTERFACE)

target_include_directories(tst INTERFACE include/)

if(BUILD_TESTING)
  create_test(NAME tst-test SOURCES test/tst-test.cxx)
  target_link_libraries(tst-test tst doctest::doctest)
endif()
