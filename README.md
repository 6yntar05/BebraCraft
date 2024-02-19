# BebraCraft
Student's laboratory work. OpenGL C++ Minecraft (not)clone

![BebraCraft Screenshot](/Screenshot.png?raw=true "BebraCraft")

## Dependencies
### Archlinux
- `sudo pacman -S cmake gcc sdl2 sdl2_image sdl2_ttf glew glm freetype2 spdlog`
### Debian/Ubuntu
- `sudo apt update # && sudo apt upgrade`
- `sudo apt install build-essential cmake extra-cmake-modules libopengl-dev libglx-dev libglu1-mesa-dev libglm-dev libglew-dev glew-utils libsdl2-dev libfreetype-dev libspdlog-dev`
### FreeBSD
- `sudo pkg install cmake gcc sdl2 sdl2_image sdl2_ttf glew glm freetype2 spdlog`
- `# NOTE: FreeBSD stores headers/libs in /usr/local dir; Just use meson build`
### RaspberryPi
- Look at 'raspberrypi' branch (TODO: OpenGL ES)

## Building via cmake
- `git clone https://github.com/6yntar05/BebraCraft`
- `git submodule init; git submodule update`
  - `# CMAKE:`
  - `mkdir build; cd build; cmake ..; cmake --build ./ -j${nproc}`
  <br>OR
  - `# MESON:`
  - `meson setup build; cd build; meson compile -j${nproc}`
- `./BebraEngine`
  
## Building via conan + cmake
- `conan install .. -vvv --build=missing`
- `conan build -vvv --build=missing ..`

## Building for Emscripten/WebGL
- `conan install .. -vvv --build=missing -pr:b default -pr:h emscripten ..`
- `conan build -vvv --build=missing -pr:b default -pr:h emscripten ..`