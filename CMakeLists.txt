#-------------------------------------------------------
# moFileReader Main Build Script
#-------------------------------------------------------
cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 11)

project(moFileReader)

add_executable(moReader ${CMAKE_SOURCE_DIR}/src/mo.cpp)
target_include_directories(moReader PRIVATE ${CMAKE_SOURCE_DIR}/include)

install(TARGETS moReader 
	RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include/)

option(BUILD_TEST "Set this to ON if you want to build the test" OFF)

if(BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()