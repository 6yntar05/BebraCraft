#include <exception>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>

#include "engine/core.h"

namespace bebra {

    void init(const gapi gApi) {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cout << "[ERROR] SDL::INIT" << std::endl << SDL_GetError() << std::endl;
            throw std::exception();
        }

        switch (gApi) {
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

                // Other SDL OpenGL attributes
                SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
                break;

            default:
                throw std::invalid_argument("Not implemented gapi, or null");
        }
    }

    SDL_Window* window(const std::string windowName, const uint windowWidth, const uint windowHeight, const uint32_t properties_graphic_api) {
        // SDL hints
        SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "1"); //Keep X11 compositor enable
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    
        // -1 - Adaptive VSYNC, 
        SDL_GL_SetSwapInterval(0);

        // Creating window
        SDL_Window *window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight, properties_graphic_api);
        if (window == NULL) {
            std::cerr << "ERROR::SDL::CREATE_WINDOW" << std::endl;
            throw std::exception();
        }

        // Grabbing input
        SDL_SetWindowGrab(window, SDL_TRUE);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        return window;
    }
    
    void contextCreate(SDL_Window* const window, const uint windowWidth, const uint windowHeight, const bool nicest) {
        // Creating context itself
        SDL_GL_CreateContext(window);
        glewInit();

        // Tuning context
        glViewport(0, 0, windowWidth, windowHeight);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Sometime earlier, without it, it was bad with textures

        if (nicest) {
            glEnable(GL_MULTISAMPLE);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
            glEnable(GL_LINE_SMOOTH);
        }
    }
}
