cmake_minimum_required(VERSION 3.20)

project(vec3)

add_executable(test
    main.cpp
    vec3.hpp
    vec3.cpp)

set_target_properties(test PROPERTIES CXX_STANDARD 23)
