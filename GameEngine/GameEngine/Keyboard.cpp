#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Keyboard.hpp"

Keyboard::Keyboard()
  :keysArray(NULL), Input(false)
{};

Keyboard::~Keyboard()
{};

Uint8* Keyboard::GetKeyArray()
{
  return keysArray;
}
std::string Keyboard::GetText()
{
  return text;
};

void Keyboard::StopBuildText(bool clear)
{
  SDL_StopTextInput();
  if (clear)
    text.clear();
  Input = false;
};

void Keyboard::StartBuildText()
{
  SDL_StartTextInput();
  Input = true;
};

void Keyboard::BuildText(SDL_Event event)
{
  if (!Input)
    return;

  if (event.type == SDL_TEXTINPUT) 
    text += event.text.text;
  
  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE) 
    text.pop_back();
};

void Keyboard::Update()
{
  SDL_PumpEvents();
  keysArray = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
};
