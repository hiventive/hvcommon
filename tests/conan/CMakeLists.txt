project(PackageTest CXX)
enable_language(C) # Fix CMake 3.1.0 (at least) thread issue
cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(HVCommon 0.1.0 REQUIRED CONFIG)

add_executable(example example.cpp)
target_link_libraries(example HV::common)

enable_testing()
add_test(NAME example
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         COMMAND example)
