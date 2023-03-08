# BebraCraft
Students laboratory work. OpenGL C++ Minecraft (not)clone

![BebraCraft Screenshot](/Screenshot.png?raw=true "BebraCraft")

## Installation
### Archlinux
- `sudo pacman -S sdl2 glew glm stb`
- `# and glfw-x11 or glfw-wayland`
### Debian/Ubuntu
- `sudo apt update # && sudo apt upgrade`
- `sudo apt install build-essential cmake extra-cmake-modules libopengl-dev libglx-dev libglu1-mesa-dev libglm-dev libglew-dev glew-utils libsdl2-dev libstb-dev`
### RaspberryPi
- Look at 'raspberrypi' branch

## Building
- `git clone https://github.com/6yntar05/BebraCraft`
- `mkdir build; cd build`
- `cmake ..; cmake --build ./ -j${nproc}`
- `./BebraEngine`