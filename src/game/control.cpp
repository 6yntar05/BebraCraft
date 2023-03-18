#include "game/control.h"

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

void handleInput(std::list<SDL_Keycode>& keyPressed, float& speed, float& yaw, float& pitch, bool& window_running) {
    bebra::pullEvents(keyPressed, speed, yaw, pitch, window_running);
    
    for (auto key : keyPressed) {
        switch (key) {
            case SDLK_ESCAPE:
                window_running = false;
                break;

            case SDLK_w:
                cameraPos += glm::normalize(
                    glm::cross(
                        glm::cross(cameraFront, cameraUp), glm::vec3(0.0,-1.0,0.0)
                    )
                    ) * speed;
                break;

            case SDLK_a:
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
                break;

            case SDLK_s: //
                cameraPos += glm::normalize(
                    glm::cross(
                        glm::cross(cameraFront, cameraUp), glm::vec3(0.0,1.0,0.0)
                    )
                    ) * speed;
                break;

            case SDLK_d:
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
                break;

            case SDLK_SPACE:
                cameraPos[1] += speed;
                break;
            
            case SDLK_LSHIFT:
                cameraPos[1] -= speed;
                break;

            case SDLK_UP:
                pitch += 2.0f;
                break;

            case SDLK_LEFT:
                yaw -= 2.0f;
                break;

            case SDLK_DOWN:
                pitch -= 2.0f;
                break;

            case SDLK_RIGHT:
                yaw += 2.0f;
                break;

            default:
                break;
        }
    }
    if (pitch > 89.0) pitch = 89.0;
    else if (pitch < -89.0) pitch = -89.0;
}