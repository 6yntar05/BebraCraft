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
    SDL_Window* window(std::string windowName, uint windowWidth, uint windowHeight, uint32_t properties_graphic_api);
    void contextCreate(SDL_Window* window, uint windowWidth, uint windowHeight, bool debugVerticles = false, bool nicest = true);
    
}