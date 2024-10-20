cmake_minimum_required(VERSION 3.10)
project(compiler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(compiler
                        src/main.cpp
              )

target_compile_features(compiler PRIVATE cxx_std_17)