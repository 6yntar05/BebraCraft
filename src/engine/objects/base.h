#pragma once
#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine/graphics/textures.h>

namespace bebra {
namespace objects {

    enum objIdent {
        ebase,
        eblock,
        eglass,
        //eleaves,
        eplant,
        efluid
    };

    struct objectTexture {
        GLuint textureArray;
        uint arraySize;
        
        objectTexture() : arraySize(0) {}
        objectTexture(std::vector<std::string> pathes)
            : arraySize(pathes.size()) {
            this->textureArray = graphics::loadTextureArray(pathes);
        }
        objectTexture(std::string path, uint count = 6)
            : arraySize(count) {
            std::vector<std::string> pathes;
            for (uint i = 0; i < count; i++)
                pathes.push_back(path);
            this->textureArray = graphics::loadTextureArray(pathes);
        }
    };

    class object {
      public:
        // Structure and textures
        static constexpr float verticies[] = {{}};
        static constexpr GLuint indices[] = {{}};
        objectTexture texture;

        // Position
        float rotate;

        // Render
        static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
            std::cerr << "Wtf its base object" << std::endl;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindVertexArray(0);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        };

        // Service
        objIdent id = objIdent::ebase;
        object() {};
        object(objIdent id) : id(id) {};
        object(objectTexture texture, float rotate = 0.0)
            : texture(texture), rotate(rotate) {}
    };

}
}