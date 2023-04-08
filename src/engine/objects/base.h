#pragma once
#include <array>
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

namespace bebra::objects {

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

enum ObjIdent { // todo: transparent and semitransparent instead glass, fluid...
    ebase,
    eblock,
    eglass,
    eplant,
    efluid
};

struct ObjectTexture {
    GLuint textureArray;
    uint arraySize;
    
    ObjectTexture() : arraySize(0) {}
    ObjectTexture(std::vector<std::string> pathes)
        : arraySize(pathes.size()) {
        this->textureArray = graphics::loadTextureArray(pathes);
    }
    ObjectTexture(std::string path, uint count = 6)
        : arraySize(count) {
        std::vector<std::string> pathes;
        for (uint i = 0; i < count; i++)
            pathes.push_back(path);
        this->textureArray = graphics::loadTextureArray(pathes);
    }
};

class Object {
    public:
    // Structure and textures
    static constexpr std::array<Vertex,36> vertices = {};
    static constexpr std::array<GLuint,6> indices = {};
    ObjectTexture texture;

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
    ObjIdent id = ObjIdent::ebase;
    Object() {};
    Object(ObjIdent id) : id(id) {};
    Object(ObjectTexture texture, float rotate = 0.0)
    : texture(texture), rotate(rotate) {}
};

} // namespace bebra::objects