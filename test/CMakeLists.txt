if(NOT EXISTS "${CMAKE_BINARY_DIR}/catch/catch.hpp")
	file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/catch")
    message(STATUS "Downloading catch.hpp from https://github.com/catchorg/Catch2/")
    file(DOWNLOAD "https://github.com/catchorg/Catch2/releases/download/v2.5.0/catch.hpp"
            "${CMAKE_BINARY_DIR}/catch/catch.hpp")
endif()

add_executable(moFileReaderTest test.cpp)
target_include_directories(moFileReaderTest PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/catch)
target_link_libraries(moFileReaderTest moFileReader)
add_test(NAME mo_test COMMAND moFileReaderTest)

add_custom_command(
	TARGET moFileReaderTest POST_BUILD
  	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo $<TARGET_FILE_DIR:moFileReaderTest>/test.mo
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo ${CMAKE_CURRENT_BINARY_DIR}/test.mo
)
