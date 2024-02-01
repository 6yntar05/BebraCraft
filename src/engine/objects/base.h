#pragma once
#include <engine/graphics/textures.h>

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

namespace bebra::objects {

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    //int TexIndex = 0;
};

enum ObjIdent { // todo: transparent and semitransparent instead glass, fluid...
    ebase,
    esolid,
    etransparent,
    esemitransparent,
    efluid,
    eplant
};

struct ObjectTexture {
    std::vector<graphics::Texture> textures;
    GLuint textureArray;
    unsigned int arraySize;
    
    ObjectTexture() : arraySize(0) {}
    ObjectTexture(std::vector<graphics::Texture> textures)
        : textures(textures), arraySize(textures.size()) {
        //graphics::loadTextureArray(&textureArray, textures);
        auto texture = textures.at(0);
        for (size_t i = 1; i < textures.size(); i++)
            texture.append(textures[i]);
        graphics::loadTexture(&textureArray, texture);
    }
    ObjectTexture(std::string path, unsigned int count = 6) // TODO
        : arraySize(count) {
        //std::vector<std::string> pathes;
        //for (unsigned int i = 0; i < count; i++)
        //    pathes.push_back(path);
        //this->textureArray = graphics::loadTextureArray(pathes);
        graphics::Texture texture {path};
        for (size_t i = 1; i < count; i++)
            texture.append(graphics::Texture(path));
        graphics::loadTexture(&textureArray, texture);
    }
};

class Object {
public:
    const std::string name;
    // Structure and textures
    static constexpr std::array<Vertex,24> vertices = {};
    static constexpr std::array<GLuint,36> indices = {};
    ObjectTexture texture;

    // Position
    float rotate;

    // Render
    static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
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