#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <iostream>

namespace bebra::graphics {

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
	Shader() : type(enone) {}
	Shader(const ShaderType type, const std::string path);
	//~Shader() {glDeleteShader(blob);}
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


class BlockShaderApi  {
private:
	GLint viewLoc;
	GLint projectionLoc;
	GLint worldTimeLoc;
	GLint modelLoc;

public:
	ShaderProgram program;

	void view(const glm::mat4 view);
	void projection(const glm::mat4 projection);
	void worldTime(const double time);
	void model(const glm::mat4 model);

	BlockShaderApi(const ShaderProgram shaderProgram);
};

class SkyboxShaderApi {
private:
	GLint viewLoc;
	GLint projectionLoc;
	GLint worldTimeLoc;

public:
	ShaderProgram program;

	void view(const glm::mat4 view);
	void projection(const glm::mat4 projection);
	void worldTime(const double time);

	void setData(const glm::mat4& view, const glm::mat4& projection, const double time) {
		this->view(view);
		this->projection(projection);
		this->worldTime(time);
	} // TODO: use this

	SkyboxShaderApi(const ShaderProgram shaderProgram);
};

} // namespace bebra::graphics