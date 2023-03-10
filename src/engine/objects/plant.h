#pragma once

#include "engine/objects/object.h"
#include <cmath>

namespace bebra {
namespace objects {

    struct plantTexture : objectTexture {
        plantTexture() {
            this->textures.reserve(4);
        }

        plantTexture(GLuint texture)
            : plantTexture()
        {
            this->textures = {texture, texture, texture, texture};
        }
        
        plantTexture(GLuint front, GLuint back, GLuint left, GLuint right)
            : plantTexture() 
        {
            this->textures = {front, back, left, right};
        }
    };

    class plant : public object {
      public:
        static constexpr float verticies[] = { //Coords(3), TexturesPos(2)
           -0.5f,           -0.5f, -0.5f / M_SQRT2,  0.0f, 0.0f, // Front halfinverted z
            0.5f,            0.5f,  0.5f / M_SQRT2,  1.0f, 1.0f,
            0.5f,           -0.5f,  0.5f / M_SQRT2,  1.0f, 0.0f,
            0.5f,            0.5f,  0.5f / M_SQRT2,  1.0f, 1.0f,
           -0.5f,           -0.5f, -0.5f / M_SQRT2,  0.0f, 0.0f,
           -0.5f,            0.5f, -0.5f / M_SQRT2,  0.0f, 1.0f,
          
           -0.5f,           -0.5f,  0.5f / M_SQRT2,  0.0f, 0.0f, // Back halfinverted z
            0.5f,           -0.5f, -0.5f / M_SQRT2,  1.0f, 0.0f,
            0.5f,            0.5f, -0.5f / M_SQRT2,  1.0f, 1.0f,
            0.5f,            0.5f, -0.5f / M_SQRT2,  1.0f, 1.0f,
           -0.5f,            0.5f,  0.5f / M_SQRT2,  0.0f, 1.0f,
           -0.5f,           -0.5f,  0.5f / M_SQRT2,  0.0f, 0.0f,

            0.5f / M_SQRT2,  0.5f,  0.5f,            0.0f, 1.0f, // Left halfinverted x + swiped normal
           -0.5f / M_SQRT2,  0.5f, -0.5f,            1.0f, 1.0f,
           -0.5f / M_SQRT2, -0.5f, -0.5f,            1.0f, 0.0f,
           -0.5f / M_SQRT2, -0.5f, -0.5f,            1.0f, 0.0f,
            0.5f / M_SQRT2, -0.5f,  0.5f,            0.0f, 0.0f,
            0.5f / M_SQRT2,  0.5f,  0.5f,            0.0f, 1.0f,

           -0.5f / M_SQRT2,  0.5f,  0.5f,            0.0f, 1.0f, // Right halfinverted x
            0.5f / M_SQRT2,  0.5f, -0.5f,            1.0f, 1.0f,
            0.5f / M_SQRT2, -0.5f, -0.5f,            1.0f, 0.0f,
            0.5f / M_SQRT2, -0.5f, -0.5f,            1.0f, 0.0f,
           -0.5f / M_SQRT2, -0.5f,  0.5f,            0.0f, 0.0f,
           -0.5f / M_SQRT2,  0.5f,  0.5f,            0.0f, 1.0f
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
            glBufferData(GL_ARRAY_BUFFER, sizeof(bebra::objects::plant::verticies), bebra::objects::plant::verticies, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bebra::objects::plant::indices), bebra::objects::plant::indices, GL_STATIC_DRAW);

            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // texturePosition attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            
            glBindVertexArray(0); // Unbind VAO
        }

        // Service
        static constexpr objIdent id = objIdent::eplant;
        plant() : object(id) {};
        plant(plantTexture texture, float rotate = 0.0)
            : plant()
        {
            this->texture = texture;
            this->rotate = rotate;
        }
    };

}
}