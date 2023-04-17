# BebraCraft
Student's laboratory work. OpenGL C++ Minecraft (not)clone

![BebraCraft Screenshot](/Screenshot.png?raw=true "BebraCraft")

## Installation
### Archlinux
- `sudo pacman -S cmake gcc sdl2 sdl2_image glew glm freetype2`
### Debian/Ubuntu
- `sudo apt update # && sudo apt upgrade`
- `sudo apt install build-essential cmake extra-cmake-modules libopengl-dev libglx-dev libglu1-mesa-dev libglm-dev libglew-dev glew-utils libsdl2-dev libfreetype-dev`
### RaspberryPi
- Look at 'raspberrypi' branch (TODO: OpenGL ES)

## Building
- `git clone https://github.com/6yntar05/BebraCraft`
- `git submodule init; git submodule update`
  - `# CMAKE:`
  - `mkdir build; cd build; cmake ..; cmake --build ./ -j${nproc}`
  <br>OR
  - `# MESON:`
  - `meson setup build; cd build; meson compile -j${nproc}`
- `./BebraEngine`