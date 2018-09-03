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
cmake_minimum_required(VERSION 2.6)
project(moFileReader)

# The main include directory
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/include)


# Let the user choose between static lib and dll
# To use it, call cmake -DCOMPILE_DLL=ON
option(COMPILE_DLL "Set this to ON if you want to compile the library as an DLL. When this is OFF, a static library is created (default)." OFF)


if ( NOT COMPILE_DLL )

    # Static build
    add_library(moFileReader.static STATIC ${CMAKE_SOURCE_DIR}/src/moFileReader.cpp ${CMAKE_SOURCE_DIR}/src/mo.cpp)

else ( COMPILE_DLL )

    # DLL
    add_definitions(-D_USRDLL -DMOFILE_EXPORTS)
    add_library(moFileReader SHARED ${CMAKE_SOURCE_DIR}/src/moFileReader.cpp ${CMAKE_SOURCE_DIR}/src/mo.cpp)

endif ()

add_executable(moReader ${CMAKE_SOURCE_DIR}/src/mo.cpp)

if ( NOT COMPILE_DLL )

add_definitions(-D_CONSOLE)
add_dependencies(moReader moFileReader.static)
target_link_libraries(moReader moFileReader.static)

else ( COMPILE_DLL )

add_definitions(-D_CONSOLE -DMOFILE_IMPORT)
add_dependencies(moReader moFileReader)
target_link_libraries(moReader moFileReader)

endif ()








