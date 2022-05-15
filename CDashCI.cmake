cmake_minimum_required(VERSION 3.12)

execute_process(
        COMMAND git rev-parse --short HEAD
        WORKING_DIRECTORY ${CTEST_SCRIPT_DIRECTORY}
        OUTPUT_VARIABLE GIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
cmake_host_system_information(RESULT CTEST_SITE QUERY HOSTNAME)
set(CTEST_BUILD_NAME "${CMAKE_SYSTEM}-${GIT_HASH}")

set(CTEST_SOURCE_DIRECTORY "${CTEST_SCRIPT_DIRECTORY}")
set(CTEST_BINARY_DIRECTORY "${CTEST_SCRIPT_DIRECTORY}/ci-build")

set(CTEST_CMAKE_GENERATOR Ninja)
set(CTEST_BUILD_CONFIGURATION Release)

macro(check_status res step)
    if (res)
        message(SEND_ERROR "Step ${step} failed with error code ${res}")
    endif ()
endmacro()

# start and update the dashboard
ctest_start(Continuous)

# finally do the configure, build, test and submit steps
if (UNIX AND NOT APPLE)
    set(COV_ARG "\"-DENABLE_COVERAGE=ON\"")
    find_program(GCOV_BIN gcov)
    set(CTEST_COVERAGE_COMMAND ${GCOV_BIN})
endif ()
ctest_configure(OPTIONS "-DCMAKE_BUILD_TYPE=${CTEST_BUILD_CONFIGURATION}\" ${COV_ARG} \"-DBUILD_TEST=ON" RETURN_VALUE res)
check_status("${res}" "Config")

ctest_build(RETURN_VALUE res)
check_status("${res}" "Build")

ctest_test(RETURN_VALUE res)
check_status("${res}" "Tests run")

ctest_coverage()

ctest_submit(RETURN_VALUE res)
check_status("${res}" "Submit")