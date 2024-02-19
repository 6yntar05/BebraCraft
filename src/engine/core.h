#pragma once
#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <bitset>

namespace bebra {

enum GApi {
    None,
    OpenGL,
    OpenGLES, //TODO
    WebGL // TODO
};

enum ContextFlags {
    Debug       = 1 << 1,
    AA          = 1 << 2,
    Multisample = 1 << 3
};

struct DebugVars {
    bool nohud = false;
    bool lines = false;
};

struct Window {
    SDL_Window* itself;
    std::string windowName;
    SDL_DisplayMode mode;
    DebugVars debug;    // Todo: move or rename
    
    std::bitset<4> contextFlags;
    bool isRunning;

    Window(){}; //deleteme
    Window(const std::string windowName, SDL_DisplayMode mode, const uint32_t properties_graphic_api);
    ~Window() { SDL_DestroyWindow(itself); }
};

SDL_DisplayMode init(const GApi);
SDL_GLContext glContextCreate(const Window& window, std::bitset<4> flags = {0});
//SDL_GL_DeleteContext(glContext);

}; // namespace bebra