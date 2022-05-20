cmake_minimum_required(VERSION 3.0)

project(print_ip)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall -Wextra -pedantic -Wno-unused-parameter
)

add_executable(print_ip main.cpp)

install(TARGETS print_ip RUNTIME DESTINATION bin)
