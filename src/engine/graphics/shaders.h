#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

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

        shader(const shaderType type, const std::string path) 
        : type(path.size() == 0 ? type : enone)
        {
            if (type == enone) return;
            if (path.size() == 0) return;
            const GLchar* shaderCode;
            // Read shader
            std::string code;
            std::ifstream file;
            file.exceptions(std::ifstream::badbit);
            try {
                file.open(path);
                std::stringstream stream;
                stream << file.rdbuf();
                file.close();
                code = stream.str();
            } catch (std::ifstream::failure const& e) {
                std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }

            shaderCode = code.c_str();
                
            // Compile shader
            std::string shaderName;
            switch(type) {
                case evertex:
                    blob = glCreateShader(GL_VERTEX_SHADER);
                    shaderName = "VERTEX(";
                    break;
                case egeometry:
                    blob = glCreateShader(GL_GEOMETRY_SHADER);
                    shaderName = "GEOMETRY(";
                    break;
                case efragment:
                    blob = glCreateShader(GL_FRAGMENT_SHADER);
                    shaderName = "FRAGMENT(";
                    break;
                default:
                    shaderName = "?(";
                    std::cerr << "WTF?\n";
            }
            shaderName = shaderName + path + ")";

            glShaderSource(blob, 1, &shaderCode, NULL);
            glCompileShader(blob);

            // Check for errors
            GLint success;
            GLchar infoLog[512];
            glGetShaderiv(blob, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(blob, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::"<<shaderName<<"::COMPILATION_FAILED\n" << infoLog << std::endl; // TODO
            }
        }

        ~shader() {
            glDeleteShader(blob);
        }
    };

    class shaderProgram {
      public:
        GLuint program;

        void use() {
            glUseProgram(program); 
        }

        shaderProgram(const std::string vertexPath, const std::string fragmentPath)
        : shaderProgram(vertexPath, {}, fragmentPath) {}

        shaderProgram(const std::string vertexPath, const std::string geometryPath, const std::string fragmentPath)
        : shaderProgram({shader::evertex, vertexPath}, {shader::egeometry, geometryPath}, {shader::efragment, fragmentPath}) {}

        shaderProgram(shader vertex, shader fragment)
        : shaderProgram(vertex, {}, fragment) {}

        shaderProgram(shader vertex, shader geometry, shader fragment) {
            // Shader program
            program = glCreateProgram();
            glAttachShader(program, vertex.blob);
            glAttachShader(program, fragment.blob);
            glLinkProgram(program);
            // Print linking errors if any
            GLint success;
            GLchar infoLog[512];
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::program::LINKING_FAILED\n" << infoLog << std::endl;
            }
        }

    };

}
}