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
	bool isArray = false;
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
    std::vector<unsigned int> indices;
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

	void append(const bebra::objects::Object obj, const glm::vec3& move = {0,0,0}) { // todo: move (static constexpr is a problem) // TODO REWRITE THIS SHIT
		std::array<Vertex, 36> tmpVerts;
		switch (obj.id) {
			case eblock: {
				for (size_t i = 0; i < tmpVerts.size(); i++)
					tmpVerts.at(i) = ((i < Block::vertices.size()) ? Block::vertices.at(i) : Block::vertices.at(0)); // temporary
				break;
			}
			case efluid: {
				for (size_t i = 0; i < tmpVerts.size(); i++)
					tmpVerts.at(i) = ((i < Fluid::vertices.size()) ? Fluid::vertices.at(i) : Fluid::vertices.at(0)); // temporary
				break;
			}
			case eglass: {
				for (size_t i = 0; i < tmpVerts.size(); i++)
					tmpVerts.at(i) = ((i < Glass::vertices.size()) ? Glass::vertices.at(i) : Glass::vertices.at(0)); // temporary
				break;
			}
			case eplant: {
				for (size_t i = 0; i < tmpVerts.size(); i++)
					tmpVerts.at(i) = ((i < Plant::vertices.size()) ? Plant::vertices.at(i) : Plant::vertices.at(0)); // temporary
				break;
			}
			default: break;
		}
		for (auto& i : tmpVerts) {
			i.Position += move;
		}
		this->vertices.insert(vertices.end(), tmpVerts.begin(), tmpVerts.end());
		this->indices.insert(indices.end(), Block::indices.begin(), Block::indices.end());
		//this->textures <- obj.texture.textureArray
		this->updateMesh();
	}
};

} // namespace bebra::objects