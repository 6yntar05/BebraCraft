#pragma once
#include "engine/camera.h"
#include "engine/core.h"
#include <SDL_keycode.h>
#include <list>

void handleInput(std::list<SDL_Keycode>& keyPressed, bebra::Camera& camera, bebra::Window& window, bool& isModeChanged);