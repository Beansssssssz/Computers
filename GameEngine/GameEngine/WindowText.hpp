#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Utils.hpp"

class WindowText {
public:
  WindowText(const char* fontPath, int size, std::string str = "", int maxSize = 30);
  ~WindowText();
  std::string GetText();
  void SetText(std::string str);
  void DisplayText(RenderWindow* window, Vector2i pos, RGBA color);
  void CreateSquare(RenderWindow* window, SDL_Rect rect, RGBA color);
  void ClearText();

private:
  TTF_Font* font;
  std::string text;
  int lengthMaxSize;
  int characterSize;
};
