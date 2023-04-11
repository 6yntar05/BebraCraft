#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

namespace bebra {
namespace graphics {

    class Shader {
      public:
        // Nested type
        enum ShaderType {
            evertex,
            egeometry,
            efragment,
            enone
        };

        // Shader parameters
        GLuint blob;
        const ShaderType type;

        // Service
        Shader() : type(enone) { std::cout << "Call\n";}
        Shader(const ShaderType type, const std::string path);
        ~Shader() {glDeleteShader(blob);}
    };

    class ShaderProgram {
      public:
        const GLuint program;

        void use() const {
            glUseProgram(program); 
        }

        ShaderProgram(const std::string vertexPath, const std::string fragmentPath)
        : ShaderProgram(vertexPath, {}, fragmentPath) {}

        ShaderProgram(const std::string vertexPath, const std::string geometryPath, const std::string fragmentPath)
        : ShaderProgram({Shader::evertex, vertexPath}, {Shader::egeometry, geometryPath}, {Shader::efragment, fragmentPath}) {}

        ShaderProgram(const Shader vertex, const Shader fragment)
        : ShaderProgram(vertex, {}, fragment) {}

        ShaderProgram(const Shader vertex, const Shader geometry, const Shader fragment);
    };

}
}