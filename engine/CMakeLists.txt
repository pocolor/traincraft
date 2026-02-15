cmake_minimum_required(VERSION 4.0)
project(native_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE native_engine_src
        "*.h"
        "*.cpp"
)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

add_library(native_engine SHARED ${native_engine_src})
target_include_directories(native_engine PRIVATE include)
target_link_libraries(native_engine ${JNI_LIBRARIES})
