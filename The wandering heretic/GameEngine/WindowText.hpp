#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Utils.hpp"

class WindowText {
public:
  WindowText(const char* fontPath, int size, std::string str = "", int maxSize = 30);
  ~WindowText();

  void DisplayText(Vector2i pos, RGBA color);
  void CreateSquare(SDL_Rect rect, RGBA color);

  void RemakeFont();
  void SetCharacterSize(int size);

  void SetText(std::string str);
  void ClearText();

  std::string GetText();
  int GetTextWidth();

private:
  TTF_Font* font;
  std::string text;

  int _maxLength;
  int _characterSize;
  const char* _fontPath;

  int _width;
};
