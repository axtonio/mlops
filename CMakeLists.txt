cmake_minimum_required(VERSION 3.15)
project(hw1_mlops LANGUAGES CXX)

find_package(pybind11 REQUIRED)

pybind11_add_module(_core src/main.cpp)

target_compile_features(_core PUBLIC cxx_std_11)

if(NOT MSVC)
    target_compile_options(_core PRIVATE -O3 -Wall)
endif()

install(TARGETS _core DESTINATION hw1_mlops)
