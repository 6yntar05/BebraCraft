#pragma once
#include "engine/graphics/textures.h"
#include <glm/glm.hpp>
#include <vector>

namespace bebra::utils {

static constexpr float maxLight = 255.0f;

inline void colorize(graphics::Texture& texture, glm::vec3 color, glm::vec3 light = {0,0,0}) { // TODO
    int channels = (texture.mode == GL_RGBA) ? 4 : 3;
    for (int i = 0; i < texture.width * texture.height * channels; i += channels)
        for (int channel = 0; channel < 3; channel++) {
            // Coloring
            texture.getData()[i+channel] *= color[channel];

            // Light correction
            if ((maxLight - texture.getData()[i+channel]) > (light[channel] * maxLight))
                texture.getData()[i+channel] += light[channel] * maxLight;
            else
                texture.getData()[i+channel] = maxLight;
        }
}

} // namespace bebra::utils