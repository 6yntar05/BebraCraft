#pragma once
#include "engine/objects/base.h"
#include <new>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace bebra::objects {

class Mesh {
  private:
    GLuint VAO, VBO, EBO;

	void bindBuffers();
	void unbindBuffers();
    void setupMesh();
	void updateMesh();

  public:
    // Mesh data
    std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f},   {0.0f, 0.0f}}, // Front
		{{0.5f,  0.5f, -0.5f},   {0.0f,  0.0f, -1.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f, -0.5f},   {0.0f,  0.0f, -1.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f, -0.5f},   {0.0f,  0.0f, -1.0f},   {1.0f, 1.0f}},
		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f},   {0.0f, 0.0f}},
		{{-0.5f,  0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f},   {0.0f, 1.0f}},
		
		{{-0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f},   {0.0f, 0.0f}}, // Back
		{{0.5f, -0.5f,  0.5f},   {0.0f,  0.0f,  1.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f,  0.5f},   {0.0f,  0.0f,  1.0f},   {1.0f, 1.0f}},
		{{0.5f,  0.5f,  0.5f},   {0.0f,  0.0f,  1.0f},   {1.0f, 1.0f}},
		{{-0.5f,  0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f},   {0.0f, 1.0f}},
		{{-0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f},   {0.0f, 0.0f}},

		{{0.5f,  0.5f,  0.5f},  {-1.0f,  0.0f,  0.0f},   {0.0f, 1.0f}}, // Left
		{{0.5f, -0.5f, -0.5f},  {-1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f, -0.5f},  {-1.0f,  0.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f, -0.5f},  {-1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f,  0.5f},  {-1.0f,  0.0f,  0.0f},   {0.0f, 1.0f}},
		{{0.5f, -0.5f,  0.5f},  {-1.0f,  0.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f,  0.5f,  0.5f},   {1.0f,  0.0f,  0.0f},   {0.0f, 1.0f}}, // Right
		{{-0.5f,  0.5f, -0.5f},   {1.0f,  0.0f,  0.0f},   {1.0f, 1.0f}},
		{{-0.5f, -0.5f, -0.5f},   {1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f},   {1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.5f},   {1.0f,  0.0f,  0.0f},   {0.0f, 0.0f}},
		{{-0.5f,  0.5f,  0.5f},   {1.0f,  0.0f,  0.0f},   {0.0f, 1.0f}},

		{{-0.5f,  0.5f, -0.5f},  { 0.0f, -1.0f,  0.0f},   {0.0f, 1.0f}}, // Up
		{{0.5f,  0.5f,  0.5f},   {0.0f, -1.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f, -0.5f},   {0.0f, -1.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f,  0.5f,  0.5f},   {0.0f, -1.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f,  0.5f, -0.5f},  { 0.0f, -1.0f,  0.0f},   {0.0f, 1.0f}},
		{{-0.5f,  0.5f,  0.5f},  { 0.0f, -1.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f},  { 0.0f, 1.0f}}, // Down
		{{0.5f, -0.5f, -0.5f},   {0.0f,  1.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f,  0.5f},   {0.0f,  1.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f, -0.5f,  0.5f},   {0.0f,  1.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.5f},  { 0.0f,  1.0f,  0.0f},  { 0.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f},  { 0.0f, 1.0f}}
	};
    std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};
    std::vector<GLuint> textures;

    // Service
    Mesh() {
		// Fill the buffers
		setupMesh();
	}

	void render() {
		this->bindBuffers();
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // TODO: textures
		this->unbindBuffers();
	}

	void move(glm::vec3 vec) {
		for (Vertex& i : vertices)
			i.Position += vec;
		this->updateMesh();
	}

    void operator+=(Mesh another) {
		vertices.insert(vertices.end(), another.vertices.begin(), another.vertices.end());
		indices.insert(indices.end(), another.indices.begin(), another.indices.end());
		textures.insert(textures.end(), another.textures.begin(), another.textures.end());
		this->updateMesh();
	}

	void appendObject(bebra::objects::Object* obj) {
		//obj->verticies
		//obj->indices
		//obj->texture
	}
};

} // namespace bebra::objects