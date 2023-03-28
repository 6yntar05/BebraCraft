#include "engine/graphics/cubemaps.h"

namespace bebra::graphics {

void loadObject(GLuint& VBO, GLuint& VAO) {

    float skyboxVertices[] = { //Coords(3), Normal(3)
       -1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,
        1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,
        1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,
        1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,
    
       -1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,
       -1.0f, -1.0f, -1.0f,   0.0f,  0.0f,  1.0f,
       -1.0f,  1.0f, -1.0f,   0.0f,  0.0f,  1.0f,
       -1.0f,  1.0f, -1.0f,   0.0f,  0.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,
    
        1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,
        1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,
    
       -1.0f, -1.0f,  1.0f,   1.0f,  0.0f,  0.0f,
       -1.0f,  1.0f,  1.0f,   1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,   1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,   1.0f,  0.0f,  0.0f,
        1.0f, -1.0f,  1.0f,   1.0f,  0.0f,  0.0f,
       -1.0f, -1.0f,  1.0f,   1.0f,  0.0f,  0.0f,
    
       -1.0f,  1.0f, -1.0f,   0.0f, -1.0f,  0.0f,
        1.0f,  1.0f, -1.0f,   0.0f, -1.0f,  0.0f,
        1.0f,  1.0f,  1.0f,   0.0f, -1.0f,  0.0f,
        1.0f,  1.0f,  1.0f,   0.0f, -1.0f,  0.0f,
       -1.0f,  1.0f,  1.0f,   0.0f, -1.0f,  0.0f,
       -1.0f,  1.0f, -1.0f,   0.0f, -1.0f,  0.0f,

       -1.0f, -1.0f, -1.0f,   0.0f,  1.0f,  0.0f,
       -1.0f, -1.0f,  1.0f,   0.0f,  1.0f,  0.0f,
        1.0f, -1.0f, -1.0f,   0.0f,  1.0f,  0.0f,
        1.0f, -1.0f, -1.0f,   0.0f,  1.0f,  0.0f,
       -1.0f, -1.0f,  1.0f,   0.0f,  1.0f,  0.0f,
        1.0f, -1.0f,  1.0f,   0.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0); // Unbind VAO
}

} // namespace bebra::graphics