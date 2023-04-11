#pragma once
#include "engine/graphics/textures.h"
#include <glm/glm.hpp>
#include <vector>

namespace bebra::utils {

void colorize(graphics::Texture& texture, glm::vec3 color, glm::vec3 light = {0,0,0}) { // TODO
    for (int i = 0; i < texture.width * texture.height * ((texture.mode == GL_RGBA)?4:3); i += ((texture.mode == GL_RGBA)?4:3)) {
        texture.image[i]   *= color[0];
        texture.image[i+1] *= color[1];
        texture.image[i+2] *= color[2];

        // todo: overflow
        texture.image[i]   += light[0];
        texture.image[i+1] += light[1];
        texture.image[i+2] += light[2];
    }
}

} // namespace bebra::utils