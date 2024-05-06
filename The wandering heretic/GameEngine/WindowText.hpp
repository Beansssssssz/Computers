#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Utils.hpp"

class WindowText {
public:
  WindowText(const char* fontPath = "Assets/Fonts/font.otf",
    int size = 24, std::string startingText = "", int maxSize = 30);

  void DisplayText(Vector2i pos = { -1,-1 }, SDL_Color color = { 0,0,0,255 }, bool display = true);

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

public:
  static void DisplayStaticText(std::string text, Vector2i pos, SDL_Color color,
    uint8_t letterSize, const char* fontPath = "Assets/Fonts/font.otf");

private:
  std::string text; //the text to display

  int _maxLength; //the max length of the text to display
  int _characterSize; //the character size of the text to display
  const char* _fontPath; //where the font exists

  int _width, _height; //the current width and height of the text.
    
  Vector2i _pos = Vector2i{ 0,0 }; //the starting position of the text
};
