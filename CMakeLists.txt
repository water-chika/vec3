cmake_minimum_required(VERSION 3.20)

project(vec3)

add_library(vec3
    vec3.hpp
    vec3.cpp)
set_target_properties(vec3 PROPERTIES CXX_STANDARD 23)
target_include_directories(vec3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(vec3_test
    main.cpp)

set_target_properties(vec3_test PROPERTIES CXX_STANDARD 23)

