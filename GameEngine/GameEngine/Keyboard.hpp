#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

enum class KeyboardButtons {
  moveLeft = SDLK_d,
  moveRight = SDLK_a,
  moveDown = SDLK_s,
  jump = SDLK_SPACE,
};

class Keyboard
{
public:
  Keyboard();
  ~Keyboard();
  Uint8* GetKeyArray();
  void Update();
  //void Update();

private:
  Uint8* keysArray;
};
