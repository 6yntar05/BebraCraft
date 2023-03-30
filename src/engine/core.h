#pragma once
#include <SDL2/SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

namespace bebra {

enum GApi {
    OpenGL,
    OpenGLES, // TODO
    Vulkan, // TODO
    None
};

struct Window {
    SDL_Window* itself;
    std::string windowName;
    SDL_DisplayMode mode;
    bool isRunning;

    Window(const std::string windowName, SDL_DisplayMode mode, const uint32_t properties_graphic_api);
};

SDL_DisplayMode init(const GApi);
void contextCreate(const Window& window, const bool nicest = true);

}; // namespace bebra