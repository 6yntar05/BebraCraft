#pragma once
#include <SDL2/SDL.h>
#include <list>

namespace bebra {

void pullEvents(std::list<SDL_Keycode>& keyPressed, float& speed, float& yaw, float& pitch, bool& window_running);
// Todo: debug hotkeys

}  // namespace bebra