#pragma once
#include <SDL_log.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <iostream>

namespace bebra::utils {

inline void glHandleError(const GLenum errorCode) {
    if (!errorCode)
        return;

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
    std::cerr << "GL::ERROR::" << errorCode << " -> " << error << std::endl;
}

}