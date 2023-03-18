#pragma once

#include "engine/graphics/textures.h"
#include "engine/objects/block.h"

#include <vector>
#include <string>
#include <iostream>

namespace bebra {
namespace graphics {
    
    struct cubeMap : public bebra::objects::blockTexture {};

    GLuint loadCubemap(const std::vector<std::string>& faces);
    void loadObject(GLuint& VBO, GLuint& VAO);

}
}