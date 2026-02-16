cmake_minimum_required(VERSION 4.0)

project(native_engine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE native_engine_src "src/*.cpp")

add_library(native_engine SHARED ${native_engine_src})

# JNI
find_package(JNI REQUIRED)
target_include_directories(native_engine PRIVATE ${JNI_INCLUDE_DIRS})

# glad
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PRIVATE vendor/glad/include)

# GLFW
add_subdirectory(vendor/glfw)

# glm
add_subdirectory(vendor/glm)

# link everything
target_link_libraries(native_engine PRIVATE
        ${JNI_LIBRARIES}
        glad
        glfw
        glm
)

# easier includes
target_include_directories(native_engine PRIVATE
        include
        include/jni
)
