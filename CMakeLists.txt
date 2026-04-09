cmake_minimum_required(VERSION 3.11)

project(DatabaseManager)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(SQLiteCpp)

add_executable(DatabaseManager src/DatabaseManager.h src/DatabaseManager.cpp src/common.h src/main.cpp)

target_link_libraries(DatabaseManager SQLiteCpp)

target_include_directories(DatabaseManager PUBLIC SQLiteCpp/include)