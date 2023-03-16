#pragma once

#include <GL/glew.h>

namespace bebra {
namespace graphics {

class Shader {
public:
    GLuint Program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
};

}
}