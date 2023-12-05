add_library(graph INTERFACE)

target_include_directories(graph INTERFACE include/)

target_link_libraries(graph INTERFACE pq)

if(BUILD_TESTING)
  create_test(NAME bfs-test SOURCES test/bfs-test.cxx)
  target_link_libraries(bfs-test graph doctest::doctest)

  create_test(NAME cc-test SOURCES test/cc-test.cxx)
  target_link_libraries(cc-test graph doctest::doctest)

  create_test(NAME dfs-test SOURCES test/dfs-test.cxx)
  target_link_libraries(dfs-test graph doctest::doctest)

  create_test(NAME edge-test SOURCES test/edge-test.cxx)
  target_link_libraries(edge-test graph doctest::doctest)

  create_test(NAME graph-test SOURCES test/graph-test.cxx)
  target_link_libraries(graph-test graph doctest::doctest)

  create_test(NAME mst-test SOURCES test/mst-test.cxx)
  target_link_libraries(mst-test graph doctest::doctest)

  create_test(NAME weighted-edge-test SOURCES test/weighted-edge-test.cxx)
  target_link_libraries(weighted-edge-test graph doctest::doctest)
endif()
