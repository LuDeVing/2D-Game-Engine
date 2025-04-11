# 2D Game Engine

![image](https://github.com/user-attachments/assets/f1253669-5496-488f-8a67-94115da4b5e6)

## Overview

A custom-built **2D Game Engine** written in C++ from scratch. This engine is designed for simplicity, performance, and extendability, making it a perfect starting point for both hobbyists and professional game developers alike.

## Table of Contents

- [Features](#features)
- [Usage](#usage)
- [Architecture](#architecture)
- [Examples](#examples)

## Features

- **Lightweight:** Designed with freedom in mind. Code is entirelly written in C++ and most calculations including rendering is handled on CPU.
- **Modular Design:** Easily extend or modify components to fit your project needs, even drawing is fully done in code.
- **Input Handling:** Supports keyboard, mouse, and controller inputs.
- **Flexible Scene Management:** Organize and manage game objects effectively.
- **Particle, Enemy, Camera and Scene Systems** different features to make game developement easier.

### Prerequisites

- **C++ Compiler:** Ensure you have a C++17-compatible compiler.
- **Visual Studio:** For opening the solution.
- **Additional Libraries:** – freeglut.h, glew.h, windows.h.

### Building from Source

Clone the repository:

```bash
git clone https://github.com/LuDeBing/2D-Game-Engine.git
cd 2d-game-engine
```

Open 2D-Game-Engine.sln in Visual Studio and build in either Debug or Release mode.

## Usage

Once built, the engine will launch a window ready to run your game logic.

The project is very lightweight, it does not have GUI, only code, so you have to manually write all the features.

- You can add code for when the game is instanciated here:
  ```cpp
  void OnUserCreate() {
  
  	globalvar.screenHeight = screenHeight;
  	globalvar.screenWidth = screenWidth;
  
    ...
  
  }
  ```

- You can add game code for game update here
  ```cpp
  void OnUserUpdate() {
  
  	auto start = std::chrono::high_resolution_clock::now();
  
  	//screenWidth = glutGet(GLUT_WINDOW_WIDTH);
  	//screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
  
  	globalvar.screenWidth = screenWidth;
  	globalvar.screenHeight = screenHeight;
  
  	globalvar.fullScreenHeight = GetSystemMetrics(SM_CYSCREEN);
  	globalvar.fullScreenWidth = GetSystemMetrics(SM_CXSCREEN);
  
    ...
  
  }
  ```

- For player update:
  ```cpp
  void Player::mainCicle(std::vector <Platform>& platforms, std::vector <Block*>& blocks, std::vector <Enemy*>& enemies) {
  
  	isMovingX = false;
  
  	getAirFriction(this->xDir);
  	getGravity(this->yDir);
  
  	...
  
    // add player code here
  
  }
  ```

- deltatime is globalvar.deltatime
- GetMouseX and GetMouseY for mouse inputs.
- Draw tiles ingame.
- getCreatorInputs function for getting inputs.
- if you press 9 on key pad the scene loading code will be generated.

- and many more...

## Examples

- Here is a simple scene that comes with the engine with gameplay:

[https://github.com/LuDeVing/2D-Game-Engine/blob/master/gameplay.mp4](https://github.com/LuDeVing/2D-Game-Engine/blob/master/gameplay.mp4)

- Here is exaplme of what scene printing looks like(this is a very simple and unoptimized solution I made many years ago, it can easly be changed if someone needs it to be changed.):

https://github.com/LuDeVing/2D-Game-Engine/blob/master/scene%20saving.mp4
