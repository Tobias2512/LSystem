cmake_minimum_required(VERSION 3.21)
project(MiniProject)

set(CMAKE_CXX_STANDARD 14)

add_library(LSystemLib STATIC
        Sources/LSystem.cpp Sources/Production.cpp Sources/LSystemFunctions.cpp)

target_include_directories(LSystemLib PRIVATE "Include/")

add_executable(TestSuite Test/Main.cpp Test/MainTest.cpp)

target_include_directories(TestSuite PRIVATE "Include/")

target_link_libraries(TestSuite PRIVATE LSystemLib)