#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace bebra {
namespace objects {

    struct blockTexture {
        GLuint front, back, up, down, left, right;

        blockTexture() {/*transparent... later*/}

        blockTexture(GLuint texture)
            : front(texture), back(texture), up(texture), down(texture), left(texture), right(texture)
            {}
        
        blockTexture(GLuint front, GLuint back, GLuint up, GLuint down, GLuint left, GLuint right)
            : front(front), back(back), up(up), down(down), left(left), right(right)
            {}
    };

    struct block {
        constexpr static float verticies[] = { //Coords(3), TexturesPos(2), TextureIndex(1)
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, // Front
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,

           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, // Back
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  2.0f, // Up
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  2.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  2.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  2.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  2.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  2.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  3.0f, // Down
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  3.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  3.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  3.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  3.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  3.0f,

            0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  4.0f, // Left
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  4.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  4.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  4.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  4.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  4.0f,

           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  5.0f, // Right
           -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  5.0f,
           -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  5.0f,
           -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  5.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  5.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  5.0f
        };

        constexpr static GLuint indices[] = {
            0, 1, 3, // First Poly
            1, 2, 3  // Second Poly
        };

        static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
            glGenVertexArrays(2, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(bebra::objects::block::verticies), bebra::objects::block::verticies, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bebra::objects::block::indices), bebra::objects::block::indices, GL_STATIC_DRAW);

            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // texturePosition attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            // TextureIndex attribute
            glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            
            glBindVertexArray(0); // Unbind VAO
        }

        blockTexture textures;
        float rotate = 0.0;
        bool air = false;
        glm::vec3 pos = {0.0, 0.0, 0.0}; // Will be ignored if in chunk (Will solving later)

        //block(blockTexture textures) : textures(textures) {}
    };

    block air { {}, 0.0, true };
}
}