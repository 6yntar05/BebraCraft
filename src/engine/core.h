#pragma once
#include <SDL.h>
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

struct DebugVars {
    bool nohud = false;
    bool lines = false;
};

struct Window {
    SDL_Window* itself;
    std::string windowName;
    SDL_DisplayMode mode;
    bool isRunning;
    DebugVars debug;

    Window(const std::string windowName, SDL_DisplayMode mode, const uint32_t properties_graphic_api);
    ~Window() { SDL_DestroyWindow(itself);}
};

SDL_DisplayMode init(const GApi);
SDL_GLContext glContextCreate(const Window& window, const bool nicest = true);

}; // namespace bebra