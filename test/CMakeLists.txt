if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.13/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES gtest/1.8.1@bincrafters/stable BASIC_SETUP CMAKE_TARGETS BUILD missing)

add_executable(test test.cpp)
target_link_libraries(test CONAN_PKG::gtest moFileReader)
add_test(NAME mo_test COMMAND test)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.mo DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/)