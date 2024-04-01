#pragma once

#include "TextSquare.hpp"

class SignIn
{
public:
  SignIn(SDL_Rect backgroundRect, SDL_Rect emailRect);

  void Update();

private:
  void CreateTextSquares(SDL_Rect& textRect);

  TextSquare* _email; //can be or email or username
  TextSquare* _pass;

  SDL_rect _backgroundRect;

  constexpr static uint8_t LETTER_SIZE = 20;
};

