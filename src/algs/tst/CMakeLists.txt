if(BUILD_TESTING)
  create_test(NAME tst-test SOURCES tst-test.cxx)
  target_link_libraries(tst-test doctest::doctest)
endif()
