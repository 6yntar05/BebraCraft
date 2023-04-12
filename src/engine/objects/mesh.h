#pragma once
#include "engine/graphics/textures.h"
#include "engine/objects/base.h"
#include "engine/objects/block.h"
#include "engine/objects/fluid.h"
#include "engine/objects/plant.h"
#include <new>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace bebra::objects {

struct TextureView {
	GLuint texture;	     // Single texture or array
	int arrayIndex = -1; // if -1 - isn't array
};

class Mesh {
private:
    GLuint VAO, VBO, EBO;

	void bindBuffers() const;
	void unbindBuffers() const;
    void setupMesh();

public:
	std::string name;
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    TextureView texture;

	// Space-transform data // TODO: split data
	glm::mat4 transform = glm::mat4(1.0f);

    // Service
	Mesh() : Mesh("Unnamed") {}
    Mesh(const std::string name) : name(name) {
		// Fill the buffers
		setupMesh();
	}

	void updateMesh();

	void render() const {
		glBindVertexArray(VAO);
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
		//textures.insert(textures.end(), another.textures.begin(), another.textures.end());
		this->updateMesh();
	}

	void append(const bebra::objects::Object obj, const glm::vec3 move = {0,0,0}) { // WTF
		auto appendVertices = Object::vertices;
		auto appendIndices  = Object::indices;

		switch (obj.id) {
			case efluid: {
				appendVertices = Fluid::vertices;
				appendIndices  = Fluid::indices;
				break;
			}
			case eplant: {
				appendVertices = Plant::vertices;
				appendIndices  = Plant::indices;
				break;
			}
			default: {
				appendVertices = Block::vertices;
				appendIndices  = Block::indices;
				break;
			};
		}

		for (Vertex vertex : appendVertices) {
			this->vertices.push_back({vertex.Position + move, vertex.Normal, vertex.TexCoords});
		}
		size_t appendOffset = this->vertices.size();

		for (const GLuint i : appendIndices) {
			this->indices.push_back(appendOffset + i); // WTF // .insert
			//this->textures.push_back({}); // TODO
		}

		this->updateMesh();
	}

	void setTexture(graphics::Texture raw) {
		this->texture.texture = graphics::loadTexture({raw});
	}
};

} // namespace bebra::objects