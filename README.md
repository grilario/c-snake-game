# Snake Game written in C

This Snake Game is implemented using the Raylib library, which provides a simple API for graphics and input manipulation in C. Control the snake using the arrow keys.

<p align="center">
  <img src="./assets/preview.gif" />
</p>

## Building

#### Install required tools

You need a **GCC**, **CMake** building system, and for raylib you need to install some required libraries; **ALSA** for audio, **Mesa** for OpenGL accelerated graphics and **X11** for windowing system:

##### Ubuntu/Debian

```sh
sudo apt install build-essential git cmake libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

To build the game you need to download game git repository and submodules:

```sh
git clone --recurse-submodules https://github.com/grilario/c-snake-game
```

Build and run:

```sh
cd c-snake-game
mkdir build && cd build
cmake ..
make
./snake-game
```
