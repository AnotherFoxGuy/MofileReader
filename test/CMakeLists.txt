if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.13/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES gtest/1.8.1@bincrafters/stable BASIC_SETUP CMAKE_TARGETS BUILD missing)

add_executable(moFileReaderTest test.cpp)
target_include_directories(moFileReaderTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(moFileReaderTest CONAN_PKG::gtest moFileReader)
add_test(NAME mo_test COMMAND moFileReaderTest)

add_custom_command(
	TARGET moFileReaderTest POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo $<TARGET_FILE_DIR:moFileReaderTest>/test.mo
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo ${CMAKE_CURRENT_BINARY_DIR}/test.mo
)
