#pragma once

//#include "engine/objects/base.h"
#include "engine/objects/block.h"
#include <cmath>

namespace bebra::objects {

class Plant : public Block {
    public:
    static constexpr float psize = 0.5f / M_SQRT2;
    static constexpr float dsize = psize;

    static constexpr float verticies[] = { //Coords(3), Normal(3), TexturesPos(2)
        -psize, -0.5f, -psize,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // Front halfinverted z
        psize,  dsize, psize,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        psize, -0.5f,  psize,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
        psize,  dsize, psize,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        -psize, -0.5f, -psize,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
        -psize,  dsize,-psize,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        
        -psize, -0.5f,  psize,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // Back halfinverted z
        psize, -0.5f, -psize,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
        psize,  dsize,-psize,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        psize,  dsize,-psize,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -psize,  dsize, psize,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
        -psize, -0.5f,  psize,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
    };

    static constexpr GLuint indices[] = {
        0, 1, 3, // First Poly
        1, 2, 3  // Second Poly
    };

    // Render
    static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bebra::objects::Plant::verticies), bebra::objects::Plant::verticies, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bebra::objects::Plant::indices), bebra::objects::Plant::indices, GL_STATIC_DRAW);

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
    static constexpr ObjIdent id = ObjIdent::eplant;
    Plant() : Block(id) {};
    Plant(ObjectTexture texture, float rotate = 0.0)
        : Plant()
    {
        this->texture = texture;
        this->rotate = rotate;
    }
};

} // namespace bebra::objects