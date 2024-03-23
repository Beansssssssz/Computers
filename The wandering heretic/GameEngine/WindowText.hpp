#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Utils.hpp"

class WindowText {
public:
  WindowText(const char* fontPath = "Assets/Fonts/font.otf",
    int size = 24, std::string startingText = "", int maxSize = 30);
  ~WindowText();

  void DisplayText(Vector2i pos = { -1,-1 }, SDL_Color color = { 0,0,0,255 });

  void RemakeFont();
  void SetCharacterSize(int size);
  int GetCharacterSize();

  void SetPos(Vector2i pos);
  Vector2i GetPos();

  void SetText(std::string str);
  std::string GetText();
  void ClearText();

  int GetTextWidth();
  int GetTextHeight();
  int GetMaxCharacters();
private:
  TTF_Font* _font;
  std::string text;

  int _maxLength;
  int _characterSize;
  const char* _fontPath;

  int _width, _height;

  Vector2i _pos = Vector2i{ 0,0 };//default value is {0,0}
};
