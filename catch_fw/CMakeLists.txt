cmake_minimum_required (VERSION 3.0) 
project (Catch2SampleProject)
set(CMAKE_CXX_STANDARD 14)

include_directories(src)
# if you exclude above, then tests will not able to find
# the header files

add_subdirectory(src)
add_subdirectory(test)
# add_subdirectory(lib/googletest) 
