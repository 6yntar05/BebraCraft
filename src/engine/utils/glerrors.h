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
    
    std::cerr << "Source: ";
    switch (source) {
        case GL_DEBUG_SOURCE_API: std::cerr << "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cerr << "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: std::cerr << "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION: std::cerr << "Application"; break;
        case GL_DEBUG_SOURCE_OTHER: std::cerr << "Other"; break;
    }
    std::cerr << "\nType: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: std::cerr << "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cerr << "Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY: std::cerr << "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: std::cerr << "Performance"; break;
        case GL_DEBUG_TYPE_MARKER: std::cerr << "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: std::cerr << "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP: std::cerr << "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER: std::cerr << "Other"; break;
    }
    std::cerr << "\nSeverity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: std::cerr << "high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: std::cerr << "medium"; break;
        case GL_DEBUG_SEVERITY_LOW: std::cerr << "low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "notification"; break;
    }
    std::cerr << std::endl;
}

}