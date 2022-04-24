**Firefly Engine**

A simple 2D engine and a "Space War!" game.

**Build**

Tested with Visual Studio 2022. You will also need to install [CMake](https://cmake.org/).

Required dependencies:
* SDL2 
* SDL2_image
* SDL2_ttf

Download the development versions of the libraries (I used these: [SDL2-devel-2.0.20-VC](https://github.com/libsdl-org/SDL/releases/download/release-2.0.20/SDL2-devel-2.0.20-VC.zip), [SDL2_image-devel-2.0.5-VC](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip), [SDL2_ttf-devel-2.0.18-VC](https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.0.18/SDL2_ttf-devel-2.0.18-VC.zip)).

Go to the project directory and execute the folowing commands:
```
mkdir build
cd build
cmake .. -DCMAKE_ISNTALL_PREFIX=../install -DSDL2_PATH="path to the SDL2 directory" -DSDL2_TTF_PATH="path to the SDL2_TTF directory"  -DSDL2_IMAGE_PATH="path to the SDL2_Image directory" 
cmake --build . --config Release
cmake --install .
```
