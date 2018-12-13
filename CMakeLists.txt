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
project(moFileReader)

# The main include directory
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/include)


# Let the user choose between static lib and dll
# To use it, call cmake -DCOMPILE_DLL=ON
option(COMPILE_DLL "Set this to ON if you want to compile the library as an DLL. When this is OFF, a static library is created (default)." OFF)
if (COMPILE_DLL)
    # DLL
    target_compile_definitions(moReader PRIVATE _USRDLL MOFILE_EXPORTS)
endif ()

add_library(moFileReader STATIC ${CMAKE_SOURCE_DIR}/src/moFileReader.cpp ${CMAKE_SOURCE_DIR}/src/mo.cpp)
add_executable(moReader ${CMAKE_SOURCE_DIR}/src/mo.cpp)

if (COMPILE_DLL)
    target_compile_definitions(moReader PRIVATE _CONSOLE MOFILE_IMPORT)
else ()
    target_compile_definitions(moReader PRIVATE _CONSOLE)
endif ()

add_dependencies(moReader moFileReader)
target_link_libraries(moReader moFileReader)

option(BUILD_TEST "Set this to ON if you want to build the test" OFF)

if(BUILD_TEST)
    add_subdirectory(test)
endif()





