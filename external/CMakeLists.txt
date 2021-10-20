project(lodepng)
add_library(lodepng STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lodepng)
