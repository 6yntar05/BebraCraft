#include "engine/graphics/cubemaps.h"

#include <stb/stb_image.h>

namespace bebra {
namespace graphics {

    GLuint loadCubemap(const std::vector<std::string>& faces) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++) {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return textureID;
    }

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

}
}