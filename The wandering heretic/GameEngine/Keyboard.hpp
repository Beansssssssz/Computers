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
  std::string GetText();
  void StopBuildText(bool clear = true);
  void StartBuildText();
  void BuildText(SDL_Event event);
  void Update();

private:
  Uint8* keysArray;
  std::string text;
  bool Input;
};
