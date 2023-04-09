#pragma once

#include "engine/objects/base.h"

namespace bebra::objects {

class Block : public Object {
    public:
    static constexpr std::array<Vertex,24> vertices = {{
		{{-0.5f,-0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},   {0.0f, 0.0f}}, // Front
		{{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},   {1.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},   {0.0f, 1.0f}},
		
		{{-0.5f,-0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},   {0.0f, 0.0f}}, // Back
		{{0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},   {1.0f, 1.0f}},
		{{-0.5f, 0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},   {0.0f, 1.0f}},

		{{0.5f,  0.5f,  0.5f},  {-1.0f, 0.0f,  0.0f},   {0.0f, 1.0f}}, // Left
		{{0.5f, -0.5f, -0.5f},  {-1.0f, 0.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f, -0.5f},  {-1.0f, 0.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f,  0.5f},  {-1.0f, 0.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f, 0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},   {0.0f, 1.0f}}, // Right
		{{-0.5f, 0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},   {1.0f, 1.0f}},
		{{-0.5f,-0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f,-0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f, 0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},   {0.0f, 1.0f}}, // Up
		{{0.5f,  0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},   {1.0f, 1.0f}},
		{{-0.5f, 0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f,-0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},   {0.0f, 1.0f}}, // Down
		{{0.5f, -0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f,-0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},   {0.0f, 0.0f}}
	}};

    static constexpr std::array<GLuint,36> indices = {
        0,  1,  2,   1,  0,  3,
		4,  5,  6,   6,  7,  4,
		8,  9,  10,  9,  8,  11,
		12, 13, 14,  14, 15, 12,
		16, 17, 18,  17, 16, 19,
		20, 21, 22,  22, 23, 20
	};
	
    // Render
    static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, Block::vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Block::indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // texturePosition attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); // Unbind VAO
    }

    // Service
    static constexpr ObjIdent id = ObjIdent::eblock;
    Block() : Object(id) {};
    Block(ObjIdent id) : Object(id) {};
    Block(ObjectTexture texture, float rotate = 0.0)
    : Block() {
        this->texture = texture;
        this->rotate = rotate;
    }
};

} // namespace bebra::objects