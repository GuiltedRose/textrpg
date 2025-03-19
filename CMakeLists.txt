cmake_minimum_required(VERSION 3.10)
project(TextRPG)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
add_executable(TextRPG ${SOURCES})