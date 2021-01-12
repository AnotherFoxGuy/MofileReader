set(CATCH_VERSION "v2.13.4")

if (NOT EXISTS "${CMAKE_BINARY_DIR}/catch-${CATCH_VERSION}/catch.hpp")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/catch-${CATCH_VERSION}")
    message(STATUS "Downloading catch.hpp from https://github.com/catchorg/Catch2/")
    file(DOWNLOAD "https://github.com/catchorg/Catch2/releases/download/${CATCH_VERSION}/catch.hpp"
            "${CMAKE_BINARY_DIR}/catch-${CATCH_VERSION}/catch.hpp")
endif ()

add_executable(moFileReaderTest test.cpp test2.cpp)
target_include_directories(moFileReaderTest PRIVATE ${CMAKE_SOURCE_DIR}/include "${CMAKE_BINARY_DIR}/catch-${CATCH_VERSION}")
add_test(NAME mo_test COMMAND moFileReaderTest)

add_custom_command(
        TARGET moFileReaderTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo $<TARGET_FILE_DIR:moFileReaderTest>/test.mo
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo ${CMAKE_CURRENT_BINARY_DIR}/test.mo
)
