add_library(segtree INTERFACE)

target_include_directories(segtree INTERFACE include/)

if(BUILD_TESTING)
  create_test(NAME max-segtree-test SOURCES test/max-segtree-test.cxx)
  target_link_libraries(max-segtree-test segtree doctest::doctest)
endif()
