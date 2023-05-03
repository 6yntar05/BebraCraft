cmake_minimum_required(VERSION 3.10)

set(PROG_LANG CXX)
set(SRC_DIR src)
set(PROJECT_NAME BebraCraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT OpenGL_GL_PREFERENCE) 
set(OpenGL_GL_PREFERENCE "GLVND")
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-missing-field-initializers -fdiagnostics-color=always -O0 -g)
include_directories(/usr/include/freetype2 SYSTEM)
include_directories(/usr/include/SDL2 SYSTEM)

project(${PROJECT_NAME} LANGUAGES ${PROG_LANG})
file(GLOB_RECURSE SRCFILES "${SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SRCFILES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(src res libs libs/tinygltf)
target_link_libraries(${PROJECT_NAME} GL GLEW SDL2 freetype)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/)
