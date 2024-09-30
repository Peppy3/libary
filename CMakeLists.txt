cmake_minimum_required(VERSION 3.15)

project(ary C)

add_library(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

target_include_directories(${PROJECT_NAME} PUBLIC ./include PRIVATE ./src)

add_subdirectory(src)

# The tests are in a unity build
add_executable(tests test/main.c)
target_link_libraries(tests ${PROJECT_NAME})
