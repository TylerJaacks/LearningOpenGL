cmake_minimum_required(VERSION 4.2)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLM REQUIRED)

add_library(STB_IMAGE "thirdparty/stb_image/stb_image.cpp")

add_library(GLAD "src/glad.c")
target_include_directories(GLAD PUBLIC thirdparty/glad/include)

add_executable(LearningOpenGL
        src/main.cpp
)

target_include_directories(LearningOpenGL PRIVATE ${GLFW3_INCLUDE_DIR})

target_link_libraries(LearningOpenGL OpenGL::GL ${GLFW3_LIBRARY} ${GLM_LIBRARY} STB_IMAGE GLAD)