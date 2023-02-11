#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>

namespace bebra {

    enum gapi {
        OpenGL,
        Vulkan,
        None
    };

    int init(gapi);
    SDL_Window* window(std::string windowName, uint windowWidth, uint windowHeight, uint32_t properties_graphic_api);
    void contextCreate(SDL_Window* window, uint windowWidth, uint windowHeight, bool debugVerticles = false);
};