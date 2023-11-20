add_library(pq INTERFACE)

target_include_directories(pq INTERFACE include/)

if(BUILD_TESTING)
  create_test(NAME index-min-pq-test SOURCES test/index-min-pq-test.cxx)
  target_link_libraries(index-min-pq-test pq doctest::doctest)

  create_test(NAME index-max-pq-test SOURCES test/index-max-pq-test.cxx)
  target_link_libraries(index-max-pq-test pq doctest::doctest)
endif()
