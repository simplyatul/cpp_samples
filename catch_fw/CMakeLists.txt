cmake_minimum_required (VERSION 3.0) 
project (Catch2SampleProject)
set(CMAKE_CXX_STANDARD 14)
# find_package(GitXXX REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    message("Building with GNU Tools")
endif()

include_directories(src)
# if you exclude above, then tests will not able to find
# the header files

add_subdirectory(src)
add_subdirectory(test)
# add_subdirectory(lib/googletest) 
