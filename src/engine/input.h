#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include <list>
#include <algorithm>

namespace bebra {
    inline static void pullEvents(
        std::list<SDL_Keycode>& keyPressed, float& speed, float& yaw, float& pitch, bool& window_running
    ) {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_QUIT) {
                window_running = false;
                break;

            } else if (Event.type == SDL_KEYDOWN) {
                if (std::find(keyPressed.begin(), keyPressed.end(), Event.key.keysym.sym) == keyPressed.end()) {
                    keyPressed.push_back(Event.key.keysym.sym);
                    if (Event.key.keysym.sym == SDLK_LCTRL)
                        speed *= 3.0;
                }

            } else if (Event.type == SDL_KEYUP) {
                if (Event.key.keysym.sym == SDLK_LCTRL)
                    speed /= 3.0;
                keyPressed.remove(Event.key.keysym.sym);

            } else if (Event.type == SDL_MOUSEMOTION) {
                yaw += float(Event.motion.xrel) * 0.2;
                pitch -= float(Event.motion.yrel) * 0.2;
            }
        }
    }
}