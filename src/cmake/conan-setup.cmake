cmake_minimum_required(VERSION 3.20)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
      "Downloading conan.cmake from https://github.com/conan-io/cmake-conan"
  )
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    TLS_VERIFY ON
    STATUS DOWNLOAD_STATUS
  )

  list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
  list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)

  if(${STATUS_CODE} EQUAL 0)
    message(STATUS "Download completed successfully.")
  else()
    message(FATAL_ERROR "Error occurred during download: ${ERROR_MESSAGE}")
  endif()
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/conan-dependencies.cmake)

conan_cmake_configure(
  REQUIRES ${CONAN_REQUIRES} BUILD_REQUIRES ${CONAN_BUILD_REQUIRES} GENERATORS
  cmake_find_package
)

conan_cmake_autodetect(CONAN_SETTINGS)

conan_cmake_install(
  PATH_OR_REFERENCE
  .
  BUILD
  missing
  REMOTE
  conancenter
  SETTINGS
  ${CONAN_SETTINGS}
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

include(${CMAKE_CURRENT_LIST_DIR}/conan-find-dependencies.cmake)
