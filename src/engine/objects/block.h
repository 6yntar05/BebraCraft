#pragma once

#include "engine/objects/object.h"

namespace bebra {
namespace objects {

    struct blockTexture : objectTexture {
        blockTexture() {
            this->textures.reserve(6);
        }

        blockTexture(GLuint texture)
            : blockTexture()
        {
            this->textures = {texture, texture, texture, texture, texture, texture};
        }
        
        blockTexture(GLuint front, GLuint back, GLuint up, GLuint down, GLuint left, GLuint right)
            : blockTexture() 
        {
            this->textures = {front, back, up, down, left, right};
        }
    };

    class block : public object {
      public:
        static constexpr float verticies[] = { //Coords(3), TexturesPos(2)
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Front
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Back
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Up
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Down
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Left
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Right
           -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f
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
            glBufferData(GL_ARRAY_BUFFER, sizeof(bebra::objects::block::verticies), bebra::objects::block::verticies, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bebra::objects::block::indices), bebra::objects::block::indices, GL_STATIC_DRAW);

            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // texturePosition attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            
            glBindVertexArray(0); // Unbind VAO
        }

        // Service
        block() {};
        block(blockTexture texture, float rotate = 0.0) {
            this->texture = texture;
            this->rotate = rotate;
        }
    };

}
}