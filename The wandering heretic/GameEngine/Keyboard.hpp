#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Keyboard
{
public:
  static Keyboard* GetKeyboard();
  ~Keyboard();
  Uint8* GetKeyArray();
  std::string GetText();
  void StopBuildText(bool clear = true);
  void StartBuildText();
  void BuildText(SDL_Event event);
  void Update();

private:
  Keyboard();
  static Keyboard* _keyboardPtr;

  Uint8* keysArray;
  std::string text;
  bool Input;
};
