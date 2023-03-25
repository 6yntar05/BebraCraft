#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace bebra {

    enum gapi {
        OpenGL,
        Vulkan, // long todo
        None
    };

    struct hardwareSpecs {
        uint maxTextureSlots;
        // ...
    };

    struct window {
        SDL_Window* itself;
        std::string windowName;
        uint windowWidth;
        uint windowHeight;
    };

    hardwareSpecs init(gapi);
    SDL_Window* window(const std::string windowName, const uint windowWidth, const uint windowHeight, const uint32_t properties_graphic_api);
    void contextCreate(SDL_Window* const window, const uint windowWidth, const uint windowHeight, const bool nicest = true);
};