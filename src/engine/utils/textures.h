#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace bebra::utils {

void colorize(std::vector<unsigned char> image, uint width, uint height, uint channels, glm::vec3 color) { // TODO
    for (size_t i = 0; i < width * height * channels; i += channels) {
        image[i] *= color[0];
        image[i+1] *= color[1];
        image[i+2] *= color[2];
    }
}

} // namespace bebra::utils