cmake_minimum_required (VERSION 3.0) 
project (Catch2SampleProject)
set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX)
    message("Building with GNU Tools")
endif()

set(SRC_BINARY ${CMAKE_PROJECT_NAME})
set(TST_BINARY ${CMAKE_PROJECT_NAME}_tst )

include_directories(src)
# if you exclude above, then tests will not able to find
# the header files

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)
include(CodeCoverage)
append_coverage_compiler_flags()
setup_target_for_coverage_gcovr_html( NAME coverage EXECUTABLE ${TST_BINARY} )

add_subdirectory(src)
add_subdirectory(test)

