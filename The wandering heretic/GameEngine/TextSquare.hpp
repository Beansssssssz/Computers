#pragma once

#include "Square.hpp"
#include "WindowText.hpp"

class TextSquare
{
public:
  TextSquare(Vector2i dst, uint8_t outlineSize, uint8_t characterSize, uint8_t maxLength, bool stopBuildText = true);
  ~TextSquare();

  void Update(bool inputOn = true, SDL_Color color = BLACK);
  WindowText* GetWinText();
private:
  void DisplaySquare();
  void InputText();

  constexpr static SDL_Color WHITE{255, 255, 255, 255};
  constexpr static SDL_Color BLACK{0, 0, 255, 255};

  SDL_Rect _dst;
  uint8_t _outlineSize;

  WindowText* _winText;

  bool _stopBuildText;
};

