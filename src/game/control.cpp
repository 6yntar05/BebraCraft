#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <algorithm>

#include "game/control.h"

void handleInput(std::list<SDL_Keycode>& keyPressed, bebra::Camera& camera, bebra::Window& window, bool& isModeChanged) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            window.isRunning = false;

        else if (event.type == SDL_KEYDOWN) {
            if (std::find(keyPressed.begin(), keyPressed.end(), event.key.keysym.sym) == keyPressed.end()) {
                keyPressed.push_back(event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_LCTRL)
                    camera.speed *= 3.0;
            }

        } else if (event.type == SDL_KEYUP) {
            keyPressed.remove(event.key.keysym.sym);
            if (event.key.keysym.sym == SDLK_LCTRL)
                camera.speed /= 3.0;

        } else if (event.type == SDL_MOUSEMOTION) {
            camera.yaw   += float(event.motion.xrel) * 0.2;
            camera.pitch -= float(event.motion.yrel) * 0.2;

        } else if (event.type == SDL_WINDOWEVENT) {
            isModeChanged = true;
            switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    window.mode.w = event.window.data1;
                    window.mode.h = event.window.data2;
                    SDL_Log("Window %d resized to %dx%d",
                            event.window.windowID, event.window.data1,
                            event.window.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    window.mode.w = event.window.data1;
                    window.mode.h = event.window.data2;
                    SDL_Log("Window %d size changed to %dx%d",
                            event.window.windowID, event.window.data1,
                            event.window.data2);
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    SDL_Log("Window %d gained keyboard focus",
                            event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    SDL_Log("Window %d lost keyboard focus",
                            event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    SDL_Log("Mouse entered window %d",
                            event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    SDL_Log("Mouse left window %d", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    SDL_Log("Exiting...");
                    window.isRunning = false;
                    break;
            }
        }
    }
    
    for (auto key : keyPressed) {
        switch (key) {
            case SDLK_ESCAPE:
                window.isRunning = false;
                break;

            case SDLK_w:
                camera.pos += glm::normalize(
                    glm::cross(
                        glm::cross(camera.front, camera.up), glm::vec3(0.0,-1.0,0.0)
                    )
                    ) * camera.speed;
                break;

            case SDLK_a:
                camera.pos -= glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
                break;

            case SDLK_s: //
                camera.pos += glm::normalize(
                    glm::cross(
                        glm::cross(camera.front, camera.up), glm::vec3(0.0,1.0,0.0)
                    )
                    ) * camera.speed;
                break;

            case SDLK_d:
                camera.pos += glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
                break;

            case SDLK_SPACE:
                camera.pos[1] += camera.speed;
                break;
            
            case SDLK_LSHIFT:
                camera.pos[1] -= camera.speed;
                break;

            case SDLK_UP:
                camera.pitch += 2.0f;
                break;

            case SDLK_LEFT:
                camera.yaw -= 2.0f;
                break;

            case SDLK_DOWN:
                camera.pitch -= 2.0f;
                break;

            case SDLK_RIGHT:
                camera.yaw += 2.0f;
                break;

            default:
                break;
        }
    }
    if (camera.pitch > 89.0) camera.pitch = 89.0;
    else if (camera.pitch < -89.0) camera.pitch = -89.0;
}