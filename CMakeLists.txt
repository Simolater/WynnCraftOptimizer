cmake_minimum_required(VERSION 3.24)
project(CraftOp)

find_package(nlohmann_json 3.11.2 REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(CraftOp main.cpp)
