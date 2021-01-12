project(moFileReaderTest)
find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

add_executable(${PROJECT_NAME} test.cpp link_test.cpp)
target_include_directories(moFileReaderTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
catch_discover_tests(${PROJECT_NAME})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo $<TARGET_FILE_DIR:moFileReaderTest>/test.mo
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.mo ${CMAKE_CURRENT_BINARY_DIR}/test.mo
)
