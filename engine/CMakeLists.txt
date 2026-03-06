cmake_minimum_required(VERSION 4.0)

project(engine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE engine_src "src/*.cpp")
add_library(engine SHARED ${engine_src})
target_include_directories(engine PUBLIC include)

find_package(JNI REQUIRED)
target_include_directories(engine PRIVATE ${JNI_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

target_link_libraries(engine PRIVATE
        ${JNI_LIBRARIES}
        OpenGL::GL
        glad
        glfw
        glm
        dl
        pthread
)
