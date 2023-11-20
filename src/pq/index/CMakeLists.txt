if(BUILD_TESTING)
  create_test(NAME index-min-pq-test SOURCES index-min-pq-test.cxx)
  target_link_libraries(index-min-pq-test doctest::doctest)

  create_test(NAME index-max-pq-test SOURCES index-max-pq-test.cxx)
  target_link_libraries(index-max-pq-test doctest::doctest)
endif()
