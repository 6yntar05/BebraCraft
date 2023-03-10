#pragma once

//#include "engine/objects/base.h"
#include "engine/objects/block.h"

namespace bebra {
namespace objects {

    struct fluidTexture : objectTexture {
        fluidTexture() {
            this->textures.reserve(6);
        }

        fluidTexture(GLuint texture)
            : fluidTexture()
        {
            this->textures = {texture, texture, texture, texture, texture, texture};
        }
        
        fluidTexture(GLuint front, GLuint back, GLuint left, GLuint right, GLuint up, GLuint down)
            : fluidTexture() 
        {
            this->textures = {front, back, left, right, up, down};
        }
    };

    class fluid : public block {
      public:
        static constexpr float verticies[] = { //Coords(3), Normal(3), TexturesPos(2)
           -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // Front
            0.5f,  0.4f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.8f,
            0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
            0.5f,  0.4f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.8f,
           -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
           -0.5f,  0.4f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.8f,

           -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // Back
            0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
            0.5f,  0.4f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.8f,
            0.5f,  0.4f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.8f,
           -0.5f,  0.4f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.8f,
           -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

            0.5f,  0.4f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.8f, // Left
            0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
            0.5f,  0.4f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.8f,
            0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
            0.5f,  0.4f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.8f,
            0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

           -0.5f,  0.4f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.8f, // Right
           -0.5f,  0.4f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.8f,
           -0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
           -0.5f,  0.4f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.8f,

           -0.5f,  0.4f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // Up
            0.5f,  0.4f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
            0.5f,  0.4f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
            0.5f,  0.4f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
           -0.5f,  0.4f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
           -0.5f,  0.4f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,

           -0.5f, -0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // Down
            0.5f, -0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f
        };

        // Render
        
        static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(bebra::objects::fluid::verticies), bebra::objects::fluid::verticies, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bebra::objects::fluid::indices), bebra::objects::fluid::indices, GL_STATIC_DRAW);

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
        static constexpr objIdent id = objIdent::efluid;
        fluid() : block(id) {};
        fluid(fluidTexture texture, float rotate = 0.0) 
            : fluid()
        {
            this->texture = texture;
            this->rotate = rotate;
        }
    };

}
}