cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME sport)
project(${PROJECT_NAME} C CXX)
# Исходники
file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.cpp"
    "src/*.txt"
)
add_executable(${PROJECT_NAME} ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES})
