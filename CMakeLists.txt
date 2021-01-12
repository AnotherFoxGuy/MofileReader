#-------------------------------------------------------
# moFileReader Main Build Script
#
# Defined Variables:
#   - COMPILE_DLL
#     - ON  : Compiles the code as a shared Library
#     - OFF : Compiles the code as a static Library
#   - BUILD_DEBUG
#     - ON  : Compiles Debug-Information into the output
#     - OFF : Optimizes the compilation with O2.
#
# Run cmake with -DVARNAME=ON/OFF to benefit from those
# possible settings.
#-------------------------------------------------------
cmake_minimum_required(VERSION 3.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 11)

project(moFileReader)

add_executable(moReader ${CMAKE_SOURCE_DIR}/src/mo.cpp)

target_include_directories(moReader PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_definitions(moReader PRIVATE _CONSOLE)

install(TARGETS moReader 
	RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include/)

option(BUILD_TEST "Set this to ON if you want to build the test" OFF)

if(BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()