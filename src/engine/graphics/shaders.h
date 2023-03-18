#pragma once

#include <GL/glew.h>
#include <string>

namespace bebra {
namespace graphics {

    class shader {
      public:
        // Nested type
        enum shaderType {
            evertex,
            egeometry,
            efragment,
            enone
        };

        // Shader parameters
        GLuint blob;
        const shaderType type;

        // Service
        shader() : type(enone) {}
        shader(const shaderType type, const std::string path);
        ~shader() { glDeleteShader(blob); }
    };

    class shaderProgram {
      public:
        const GLuint program;

        void use() const {
            glUseProgram(program); 
        }

        shaderProgram(const std::string vertexPath, const std::string fragmentPath)
        : shaderProgram(vertexPath, {}, fragmentPath) {}

        shaderProgram(const std::string vertexPath, const std::string geometryPath, const std::string fragmentPath)
        : shaderProgram({shader::evertex, vertexPath}, {shader::egeometry, geometryPath}, {shader::efragment, fragmentPath}) {}

        shaderProgram(const shader vertex, const shader fragment)
        : shaderProgram(vertex, {}, fragment) {}

        shaderProgram(const shader vertex, const shader geometry, const shader fragment);
    };

}
}