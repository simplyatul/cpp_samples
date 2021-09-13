cmake_minimum_required (VERSION 2.6)

project (Timer)

# Cred/Ref: https://newbedev.com/file-macro-shows-full-path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst \
    ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pthread)
