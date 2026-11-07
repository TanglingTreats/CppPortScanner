cmake_minimum_required(VERSION 3.16)
project(simpnmap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
add_executable(simpnmap
    main.cpp
)

target_include_directories(simpnmap PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)