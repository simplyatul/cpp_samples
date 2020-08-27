file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${TST_BINARY} ${TEST_SOURCES})

target_link_libraries(${TST_BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib)

