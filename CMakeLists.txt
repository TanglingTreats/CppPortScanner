cmake_minimum_required(VERSION 3.16)
project(nmap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(nmap
    main.cpp
)

target_include_directories(nmap PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)