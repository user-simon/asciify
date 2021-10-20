cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)

# asciify project

project(asciify)
add_executable(asciify ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(asciify PUBLIC lodepng)
