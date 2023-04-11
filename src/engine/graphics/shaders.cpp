#include "engine/graphics/shaders.h"
#include "engine/utils/glerrors.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace bebra {
namespace graphics {

// class shader
    Shader::Shader(const ShaderType type, const std::string path) 
    : type(path.size() ? type : enone) {
        //if (path.size() == 0) this->type = Shader::enone;
        if (this->type == enone) return;
        // Reading shader
        const GLchar* shaderCode;
        std::ifstream file;
        file.exceptions(std::ifstream::badbit);
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        std::string code {stream.str()};
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
                std::cerr << "UNKNOWN\n";
        }
        shaderName = shaderName + path + ")";
        glShaderSource(blob, 1, &shaderCode, NULL);
        glCompileShader(blob);

        // Check for errors
        GLint success;
        glGetShaderiv(blob, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(blob, 512, NULL, infoLog);
            std::cerr << "ERROR::Shader::"<<shaderName<<"::COMPILATION_FAILED\n" << infoLog
                << "Ignoring..." << std::endl;
        }
    }

// class ShaderProgram
    ShaderProgram::ShaderProgram(const Shader vertex, const Shader geometry, const Shader fragment)
    : program(glCreateProgram()) {
        // Shader program
        glAttachShader(program, vertex.blob);
        if (geometry.type != Shader::enone)
            glAttachShader(program, geometry.blob);
        glAttachShader(program, fragment.blob);
        glLinkProgram(program);
        // Print linking errors if any
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cerr << "ERROR::Shader::program::LINKING_FAILED\n" << infoLog
                << "Ignoring..." << std::endl;
        }
    }

}
}