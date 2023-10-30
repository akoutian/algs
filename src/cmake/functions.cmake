# convenience function for creating tests
function(create_test)
  set(opts)
  set(oneValueArgs NAME)
  set(multiValueArgs SOURCES)

  set(function "${CMAKE_CURRENT_FUNCTION}")
  cmake_parse_arguments(
    "${function}" "${opts}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN}
  )

  set(name ${${function}_NAME})
  set(sources ${${function}_SOURCES})
  add_executable(${name} ${sources})

  target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

  set(args "-fc")
  add_test(NAME ${name} COMMAND ${name} ${args})
endfunction()
