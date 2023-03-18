#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace bebra {

    enum gapi {
        OpenGL,
        Vulkan,
        None
    };

    int init(gapi);
    SDL_Window* window(const std::string windowName, const uint windowWidth, const uint windowHeight, const uint32_t properties_graphic_api);
    void contextCreate(SDL_Window* const window, const uint windowWidth, const uint windowHeight, const bool nicest = true);
};