#pragma once

#include "engine/camera.h"
#include "engine/core.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <glm/glm.hpp>
#include <list>

void handleInput(std::list<SDL_Keycode>& keyPressed, bebra::Camera& camera, bebra::Window& window, bool& isModeChanged);