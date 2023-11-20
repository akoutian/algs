add_library(mst INTERFACE)

target_include_directories(mst INTERFACE include/)

target_link_libraries(mst INTERFACE pq)

if(BUILD_TESTING)
  create_test(NAME edge-test SOURCES test/edge-test.cxx)
  target_link_libraries(edge-test mst doctest::doctest)

  create_test(NAME graph-test SOURCES test/graph-test.cxx)
  target_link_libraries(graph-test mst doctest::doctest)

  create_test(NAME mst-test SOURCES test/mst-test.cxx)
  target_link_libraries(mst-test mst doctest::doctest)
endif()
