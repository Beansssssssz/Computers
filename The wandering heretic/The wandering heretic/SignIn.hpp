#pragma once

#include "TextSquare.hpp"

#define EMAIL_FLAG 1
#define PASSWORD_FLAG 2


class SignIn
{
public:
  SignIn(SDL_Rect backgroundRect, Vector2i emailStartPos, int margin);
  ~SignIn();

  void Update();

private:
  void SelectFlag();
  void DisplayBackground();
  void CreateTextSquares(Vector2i& emailStartPos, int& margin);

  uint8_t _currentFlag;
  TextSquare* _email; //can be or email or username
  TextSquare* _pass;

  SDL_Rect _backgroundRect;


  constexpr static uint8_t LETTER_SIZE = 20;
  constexpr static SDL_Color BACKGROUND_COLOR{ 255,0,0,255 };
};
