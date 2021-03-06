cmake_minimum_required(VERSION 3.17)
project(aoc)
include_directories(
        /usr/local/include
        /Users/Sven/source/include/glm
        ./vcpkg/packages/catch2_x64-osx/include
)

find_package(
        Catch2
        CONFIG
        REQUIRED)

find_package(
        fmt
        CONFIG
        REQUIRED)

find_package(
        glm
        CONFIG
        REQUIRED)

find_package(
        range-v3
        CONFIG
        REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc "solve.cpp" source/include/common.h)
target_link_libraries(aoc PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
#target_link_libraries(aoc glm::glm)
target_compile_options(
        aoc
        PUBLIC $<$<CXX_COMPILER_ID:MSVC>:-W4
        -WX
        -analyze
        -wd4702>) # TODO range-v3 error