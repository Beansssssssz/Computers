#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Keyboard
{
public:
  Keyboard();
  ~Keyboard();
  Uint8* GetKeyArray();
  void Update();

private:
  Uint8* keysArray;
};
