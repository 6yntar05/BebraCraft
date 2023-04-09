#pragma once
#include "engine/objects/base.h"
#include "engine/objects/block.h"
#include "engine/objects/fluid.h"
#include "engine/objects/glass.h"
#include "engine/objects/plant.h"
#include <new>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace bebra::objects {

struct TextureView {
	GLuint texture;
	int arrayIndex = -1; // if -1 - isn't array
};

class Mesh {
private:
    GLuint VAO, VBO, EBO;

	void bindBuffers() const;
	void unbindBuffers() const;
    void setupMesh();
	void updateMesh();

public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<TextureView> textures;

    // Service
    Mesh() { // TODO
		// Fill the buffers
		setupMesh();
	}

	void render() const {
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // TODO: textures
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void move(const glm::vec3& vec) {
		for (Vertex& i : vertices)
			i.Position += vec;
		this->updateMesh();
	}

	void append(Mesh another, const glm::vec3& move = {0,0,0}) { // todo: no-copy realisation
		another.move(move);
		vertices.insert(vertices.end(), another.vertices.begin(), another.vertices.end());
		indices.insert(indices.end(), another.indices.begin(), another.indices.end());
		textures.insert(textures.end(), another.textures.begin(), another.textures.end());
		this->updateMesh();
	}

	void append(const bebra::objects::Object obj, const glm::vec3& move = {0,0,0}) {
		auto appendVertices = Object::vertices;
		auto appendIndices = Object::indices;

		switch (obj.id) {
			case eblock: {
				appendVertices = Block::vertices;
				appendIndices  = Block::indices;
				break;
			}
			case efluid: {
				appendVertices = Fluid::vertices;
				appendIndices  = Fluid::indices;
				break;
			}
			case eglass: {
				appendVertices = Glass::vertices;
				appendIndices  = Glass::indices;
				break;
			}
			case eplant: {
				appendVertices = Plant::vertices;
				appendIndices  = Plant::indices;
				break;
			}
			default: break;
		}

		for (Vertex vertex : appendVertices) {
			vertex.Position += move;
			this->vertices.push_back(vertex);
		}
		for (const GLuint i : appendIndices) {
			this->indices.push_back(i);
			this->textures.push_back({}); // TODO
		}

		this->updateMesh();
	}
};

} // namespace bebra::objects