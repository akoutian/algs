add_executable(tst main.cxx)

if(BUILD_TESTING)
  set(TEST_NAME tst-test)
  create_test(NAME "${TEST_NAME}" SOURCES tst-test.cxx)
  target_link_libraries("${TEST_NAME}" doctest::doctest)
endif()
