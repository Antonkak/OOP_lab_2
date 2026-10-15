cmake_minimum_required(VERSION 3.16)
project(lab_02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lab02_lib src/matrix.cpp src/matrix.h)
target_include_directories(lab02_lib PUBLIC src)

add_executable(lab02_main main.cpp)
target_link_libraries(lab02_main lab02_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab02_tests tests/test_matrix.cpp)
target_link_libraries(lab02_tests lab02_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab02_tests)