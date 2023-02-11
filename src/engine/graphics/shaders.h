#pragma once

#include <GL/glew.h>

namespace bebra {
namespace graphics {

class Shader {
public:
    GLuint Program;
    // Constructor generates the shader on the fly
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Uses the current shader
    void Use();
};

}
}