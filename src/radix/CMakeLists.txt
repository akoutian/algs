add_library(radix INTERFACE)

target_include_directories(radix INTERFACE include/)

if(BUILD_TESTING)
  set(TEST_NAME msd-test)
  create_test(NAME "${TEST_NAME}" SOURCES test/msd-test.cxx)
  target_link_libraries("${TEST_NAME}" radix doctest::doctest)
endif()
