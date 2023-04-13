#pragma once
#include <SDL_log.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <iostream>

namespace bebra::utils {

inline std::string glHandleError(const GLenum errorCode) {
    if (!errorCode)
        return {};

    std::string error;
    switch (errorCode) {
        case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE: error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW: error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW: error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
    }
    error = std::string("GL::ERROR::") + std::to_string(errorCode) + " -> " + error;
    std::cerr << error << std::endl;
    return error;
}

inline void glDebugOutput(
    GLenum source, GLenum type, unsigned int id,
    GLenum severity, GLsizei length, const char *message, const void *userParam
) {
    // Unnecessary reports
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 
 
    std::cerr << "---------------\n";
    std::cerr << "GL Debug message:  ID " << id << " => " <<  message << std::endl;
    
    std::cout << "Source: ";
    switch (source) {
        case GL_DEBUG_SOURCE_API: std::cout << "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cout << "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: std::cout << "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION: std::cout << "Application"; break;
        case GL_DEBUG_SOURCE_OTHER: std::cout << "Other"; break;
    }
    std::cout << "\nType: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: std::cout << "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cout << "Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY: std::cout << "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: std::cout << "Performance"; break;
        case GL_DEBUG_TYPE_MARKER: std::cout << "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: std::cout << "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP: std::cout << "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER: std::cout << "Other"; break;
    }
    std::cout << "\nSeverity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: std::cout << "high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: std::cout << "medium"; break;
        case GL_DEBUG_SEVERITY_LOW: std::cout << "low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "notification"; break;
    }
    std::cerr << std::endl;
}

}