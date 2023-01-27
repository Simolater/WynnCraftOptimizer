cmake_minimum_required(VERSION 3.24)
project(CraftOpt)

add_subdirectory(json)

set(CMAKE_CXX_STANDARD 23)

add_executable(CraftOpt Ingredients.cpp Ingredients.h main.cpp Optimizer.h Optimizer.cpp Result.cpp)
target_link_libraries(CraftOpt PRIVATE nlohmann_json::nlohmann_json)
