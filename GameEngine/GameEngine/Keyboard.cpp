#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Keyboard.hpp"

Keyboard::Keyboard()
  :keysArray(NULL)
{};

Keyboard::~Keyboard()
{};

Uint8* Keyboard::GetKeyArray()
{
  return keysArray;
};

void Keyboard::Update()
{
  SDL_PumpEvents();
  keysArray = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
}
