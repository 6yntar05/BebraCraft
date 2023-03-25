#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace bebra {
namespace graphics {

    GLuint createTexture(
        const GLint internalformat, const uint width, const uint height,
        const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
    );
    void loadTexture(GLuint* const texture, const std::string path);
    void loadTextureArray(GLuint* const texture, std::vector<std::string> pathes);
    GLuint loadTextureArray(std::vector<std::string> pathes);

}
}