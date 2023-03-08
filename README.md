# BebraCraft (RaspberryPI branch)
Seems layout didnt work on opengl 2.1, but mesa still compilling this shader even with errors

![BebraCraft Screenshot](/Screenshot.png?raw=true "BebraCraft")

## Installation
### Debian/Ubuntu/RpiOS/...
- `sudo apt update # && sudo apt upgrade`
- `sudo apt install build-essential cmake extra-cmake-modules libopengl-dev libglx-dev libglu1-mesa-dev libglm-dev libglew-dev glew-utils libsdl2-dev libstb-dev`

## Building
- `git clone https://github.com/6yntar05/BebraCraft --branch raspberrypi`
- `mkdir build; cd build`
- `cmake ..; cmake --build ./ -j${nproc}`
- `./BebraEngine`