# Navs Engine

A minimal lightweight engine that uses SDL3 to display graphics, animation, physics, tilemaps and more

# How to Build

Some dependencies are needed, only the include folder, if your building on windows i'd recommend you use MinGW,
for some unix-like commands.

[SDL3](https://github.com/libsdl-org/SDL)

[SDL_Image](https://github.com/libsdl-org/SDL_image)

[TMX Loader](https://github.com/baylej/tmx) (Already in repo)

clone those in some way or another. if your too lazy to think yourself follow the commands, otherwise just copy the include
folders from these repos and make a new "include" folder in the directory /Navs-Engine/

## Windows

```bash

mkdir Navs-Engine/include
git clone https://github.com/libsdl-org/SDL
mv SDL/include/SDL3 Navs-Engine/include
rm -r SDL
git clone https://github.com/libsdl-org/SDL_image
mv SDL_image/include/SDL3_image/SDL_image.h Navs-Engine/include/SDL3
rm -r SDL_image
cd Navs-Engine
build.bat
navsengine

```

Not a fan of windows but thankfully CMake exists

## Linux

```bash

mkdir Navs-Engine/include
git clone https://github.com/libsdl-org/SDL
mv SDL/include/SDL3 Navs-Engine/include
rm -r SDL
git clone https://github.com/libsdl-org/SDL_image
mv SDL_image/include/SDL3_image/SDL_image.h Navs-Engine/include/SDL3
rm -r SDL_image
cd Navs-Engine
sh build.sh
./navsengine

```

Its only an executable for now just for testing. However i will make this engine build into a shared library






