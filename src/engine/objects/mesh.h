#pragma once
#include <new>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace bebra::objects {

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
  private:
    GLuint VAO, VBO, EBO;

    void setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
					&indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void updateMesh() {} // TODO

  public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLuint> textures;

    // Service
    Mesh() { // test
		vertices = {
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
		indices = {
			0, 1, 3,
			1, 2, 3
		};
		
		setupMesh();
	}

	void render() {
		// bind
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// render
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		
		// unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void move(glm::vec3 vec) {
		for (Vertex& i : vertices) {
			i.Position += vec;
		}
		setupMesh(); //
	}

    void operator+= (Mesh another) {
		vertices.insert(vertices.end(), another.vertices.begin(), another.vertices.end());
		indices.insert(indices.end(), another.indices.begin(), another.indices.end());
		textures.insert(textures.end(), another.textures.begin(), another.textures.end());
		setupMesh(); //
	}
};

} // namespace bebra::objects