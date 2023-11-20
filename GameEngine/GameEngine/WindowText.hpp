#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Math.hpp"

class WindowText {
public:
  WindowText(const char* fontPath, int size, std::string str = "");
  ~WindowText();
  std::string GetText();
  void SetText(std::string str);
  void DisplayText(RenderWindow* window, Vector2i pos, RGBA color);
  void ClearText();

private:
  TTF_Font* font;
  std::string text;
};
