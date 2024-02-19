#include "engine/core.h"
#include "engine/utils/glerrors.h"

#include <exception>
#include <iostream>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <SDL_render.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5_webgl.h>
    #include <emscripten/wasmfs.h>
#endif


namespace bebra {

void init() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "[ERROR] SDL::INIT" << std::endl << SDL_GetError() << std::endl;
        throw std::exception();
    }

    // Init FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cerr << "FREETYPE::INIT::ERROR. Ignoring..." << std::endl;
}

SDL_DisplayMode getDisplay() {
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0,&displayMode);
    return displayMode;
}

Window::Window(const std::string windowName, SDL_DisplayMode mode, const uint32_t properties_graphic_api)
: windowName(windowName), mode(mode), isRunning(true), itself(nullptr) {
    // SDL hints
#ifndef __EMSCRIPTEN__ //or android
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "1"); //Keep X11 compositor enable
#endif
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

    // -1 - Adaptive VSYNC,
    SDL_GL_SetSwapInterval(1);

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
    std::cerr << SDL_GetError() << std::endl;
}

SDL_GLContext glContextCreate(const Window& window, const GApi gapi, std::bitset<4> flags) {
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
            // Setting OpenGL ES version
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

            // Setting SDL buffers
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);
            break;
        
        case WebGL:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            break;

        default:
            throw std::invalid_argument("Not implemented gapi, or null");
    }

    // Creating context itself
#ifdef __EMSCRIPTEN__
    SDL_GLContext context = nullptr;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_eglContext;
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.explicitSwapControl = EM_TRUE;
    m_eglContext = emscripten_webgl_create_context("canvas", &attr);
    emscripten_webgl_make_context_current(m_eglContext);
    std::cout << "Canvas initialized!" << std::endl;
#else
    SDL_GLContext context = SDL_GL_CreateContext(window.itself);
    if (!context)
        std::cerr << "Failed to create OpenGL ES context: " << SDL_GetError() << std::endl;

    if (SDL_GL_MakeCurrent(window.itself, context) < 0)
        std::cerr << "Failed to make OpenGL ES context current: " << SDL_GetError() << std::endl;
#endif

    glewInit();

    // Tuning context
    glViewport(0, 0, window.mode.w, window.mode.h);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

#ifndef __EMSCRIPTEN__
    // Context flags:
    //window.contextFlags = flags;
    if ((std::bitset<4>(ContextFlags::Debug) & flags)!=0) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
        // Initialise debug output
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//#ifdef __EMSCRIPTEN__
//        glDebugMessageCallback(utils::glDebugOutput, nullptr);
//        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//#endif
    }
    if ((std::bitset<4>(ContextFlags::AA) & flags)!=0) {
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
    }
    if ((std::bitset<4>(ContextFlags::Multisample) & flags)!=0) {
        glEnable(GL_MULTISAMPLE);
    }
#endif

    return std::move(context);
}

}  // namespace bebra
