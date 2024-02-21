cmake_minimum_required(VERSION 3.15)

# Properties
set(PROG_LANG CXX)
set(SRC_DIR src)
set(PROJECT_NAME BebraCraft)

set (CMAKE_CXX_STANDARD 20)
if(NOT OpenGL_GL_PREFERENCE) 
    set(OpenGL_GL_PREFERENCE "GLVND")
endif()
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wno-unused-command-line-argument")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -fdiagnostics-color=always")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -fcolor-diagnostics")
endif ()
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (EMSCRIPTEN)
    include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -ferror-limit=100 -sMAXIMUM_MEMORY=1gb -sALLOW_MEMORY_GROWTH=1")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=100 -sMAXIMUM_MEMORY=1gb")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sMIN_WEBGL_VERSION=2 -sUSE_WEBGL2=1 -sFULL_ES3=1 -sOFFSCREEN_FRAMEBUFFER=1 -sUSE_SDL=2") #-sFULL_ES2=1
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sFORCE_FILESYSTEM -sWASMFS -sMALLOC=emmalloc")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_BINARY_DIR}/textures@textures --preload-file ${CMAKE_BINARY_DIR}/shaders@shaders --preload-file ${CMAKE_BINARY_DIR}/fonts@fonts")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sASSERTIONS -gsource-map")
    add_definitions(-D__EMSCRIPTEN__)
endif ()

# Sources
project(${PROJECT_NAME} LANGUAGES ${PROG_LANG})
file(GLOB_RECURSE SRCFILES "${SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SRCFILES})

# Deps
include_directories(/usr/include/freetype2 SYSTEM)
include_directories(/usr/include/SDL2 SYSTEM)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2)
#find_package(freetype)

include_directories(src res libs libs/tinygltf libs/glm)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CONAN_INCLUDE_DIRS}    
    glm
    spdlog::spdlog
    )
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CONAN_LIBS}
    GL
    GLEW
    freetype
    SDL2
    spdlog
    )

add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD #Prebuild for embeding
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/
)

install(TARGETS BebraCraft DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )