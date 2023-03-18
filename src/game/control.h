#pragma once

#include <engine/input.h>
#include <glm/glm.hpp>

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

void handleInput(std::list<SDL_Keycode>& keyPressed, float& speed, float& yaw, float& pitch, bool& window_running);