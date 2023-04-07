#pragma once

//#include "engine/objects/base.h"
#include "engine/objects/block.h"

namespace bebra::objects {

class Fluid : public Block {
    public:
    static constexpr std::array<Vertex,36> vertices = {{
		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f},   {0.0f, 0.0f}}, // Front
		{{0.5f,  0.4f, -0.5f},   {0.0f,  0.0f, -1.0f},   {1.0f, 0.8f}},
		{{0.5f, -0.5f, -0.5f},   {0.0f,  0.0f, -1.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.4f, -0.5f},   {0.0f,  0.0f, -1.0f},   {1.0f, 0.8f}},
		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f},   {0.0f, 0.0f}},
		{{-0.5f,  0.4f, -0.5f},  { 0.0f,  0.0f, -1.0f},   {0.0f, 0.8f}},
		
		{{-0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f},   {0.0f, 0.0f}}, // Back
		{{0.5f, -0.5f,  0.5f},   {0.0f,  0.0f,  1.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.4f,  0.5f},   {0.0f,  0.0f,  1.0f},   {1.0f, 0.8f}},
		{{0.5f,  0.4f,  0.5f},   {0.0f,  0.0f,  1.0f},   {1.0f, 0.8f}},
		{{-0.5f, 0.4f,  0.5f},  { 0.0f,  0.0f,  1.0f},   {0.0f, 0.8f}},
		{{-0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f},   {0.0f, 0.0f}},

		{{0.5f,  0.4f,  0.5f},  {-1.0f,  0.0f,  0.0f},   {0.0f, 0.8f}}, // Left
		{{0.5f, -0.5f, -0.5f},  {-1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.4f, -0.5f},  {-1.0f,  0.0f,  0.0f},   {1.0f, 0.8f}},
		{{0.5f, -0.5f, -0.5f},  {-1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,  0.4f,  0.5f},  {-1.0f,  0.0f,  0.0f},   {0.0f, 0.8f}},
		{{0.5f, -0.5f,  0.5f},  {-1.0f,  0.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f,  0.4f,  0.5f},   {1.0f,  0.0f,  0.0f},   {0.0f, 0.8f}}, // Right
		{{-0.5f,  0.4f, -0.5f},   {1.0f,  0.0f,  0.0f},   {1.0f, 0.8f}},
		{{-0.5f, -0.5f, -0.5f},   {1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f},   {1.0f,  0.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.5f},   {1.0f,  0.0f,  0.0f},   {0.0f, 0.0f}},
		{{-0.5f,  0.4f,  0.5f},   {1.0f,  0.0f,  0.0f},   {0.0f, 0.8f}},

		{{-0.5f,  0.4f, -0.5f},  { 0.0f, -1.0f,  0.0f},   {0.0f, 1.0f}}, // Up
		{{0.5f,   0.4f,  0.5f},   {0.0f, -1.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f,   0.4f, -0.5f},   {0.0f, -1.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f,   0.4f,  0.5f},   {0.0f, -1.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f,  0.4f, -0.5f},  { 0.0f, -1.0f,  0.0f},   {0.0f, 1.0f}},
		{{-0.5f,  0.4f,  0.5f},  { 0.0f, -1.0f,  0.0f},   {0.0f, 0.0f}},

		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f},  { 0.0f, 1.0f}}, // Down
		{{0.5f, -0.5f, -0.5f},   {0.0f,  1.0f,  0.0f},   {1.0f, 1.0f}},
		{{0.5f, -0.5f,  0.5f},   {0.0f,  1.0f,  0.0f},   {1.0f, 0.0f}},
		{{0.5f, -0.5f,  0.5f},   {0.0f,  1.0f,  0.0f},   {1.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.5f},  { 0.0f,  1.0f,  0.0f},  { 0.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f},  { 0.0f, 1.0f}}
	}};
    
    static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

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
    static constexpr ObjIdent id = ObjIdent::efluid;
    Fluid() : Block(id) {};
    Fluid(ObjectTexture texture, float rotate = 0.0) 
    : Fluid() {
        this->texture = texture;
        this->rotate = rotate;
    }
};

} // namespace bebra::objects