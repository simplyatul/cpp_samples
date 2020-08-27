file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${SRC_BINARY}_run ${SOURCES})
add_library(${SRC_BINARY}_lib STATIC ${SOURCES})
# above is used to include the code in unit tests
# see target_link_libraries in test/CMakeLists.txt

