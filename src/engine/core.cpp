#include <exception>
#include <iostream>

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <SDL_render.h>
#include <SDL_image.h>

#include "engine/core.h"

namespace bebra {

SDL_DisplayMode init(const GApi gapi) {
    // Init SDL
    SDL_DisplayMode displayMode;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "[ERROR] SDL::INIT" << std::endl << SDL_GetError() << std::endl;
        throw std::exception();
    }
    SDL_GetDesktopDisplayMode(0,&displayMode);

    // Init FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cerr << "FREETYPE::INIT::ERROR. Ignoring..." << std::endl;

    // Init Graphics API
    switch (gapi) {
        case OpenGL:
            // Setting OpenGL version
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            
            // Setting SDL buffers
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);
            break;
        
        case OpenGLES:
            // Setting OpenGLES version
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

            // Setting SDL buffers
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);
            break;

        default:
            throw std::invalid_argument("Not implemented gapi, or null");
    }

    return displayMode;
}

Window::Window(const std::string windowName, SDL_DisplayMode mode, const uint32_t properties_graphic_api)
: windowName(windowName), mode(mode), isRunning(true) {
    // SDL hints
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "1"); //Keep X11 compositor enable
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

    // -1 - Adaptive VSYNC,
    SDL_GL_SetSwapInterval(0);

    // Creating window
    this->itself = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        mode.w, mode.h, properties_graphic_api);
    if (this->itself == NULL) {
        std::cerr << "ERROR::SDL::CREATE_WINDOW" << std::endl;
        throw std::exception();
    }

    // Grabbing input
    SDL_SetWindowGrab(this->itself, SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

SDL_GLContext glContextCreate(const Window& window, const bool nicest) {
    // Creating context itself
    SDL_GLContext context = SDL_GL_CreateContext(window.itself);
    glewInit();

    // Tuning context
    glViewport(0, 0, window.mode.w, window.mode.h);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // For fonts rendering

    if (nicest) {
        glEnable(GL_MULTISAMPLE);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glEnable(GL_LINE_SMOOTH);
    }

    return std::move(context);
}

}  // namespace bebra
