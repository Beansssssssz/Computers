#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Utils.hpp"

class WindowText {
public:
  WindowText(const char* fontPath = "Assets/Fonts/font.otf",
    int size = 24, std::string str = "", int maxSize = 30);
  ~WindowText();

  void DisplayText(Vector2i pos = { -1,-1 }, SDL_Color color = { 0,0,0,255 });
  void CreateSquare(SDL_Rect rect, SDL_Color color);

  void RemakeFont();
  void SetCharacterSize(int size);
  void SetPos(Vector2i pos);

  void SetText(std::string str);
  void ClearText();

  std::string GetText();
  int GetTextWidth();
  Vector2i GetPos();

private:
  TTF_Font* font;
  std::string text;

  int _maxLength;
  int _characterSize;
  const char* _fontPath;

  int _width;

  Vector2i _pos = Vector2i{ 0,0 };//default value is {0,0}
};
