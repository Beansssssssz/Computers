#include "SignIn.hpp"

SignIn::SignIn(SDL_Rect backgroundRect, SDL_Rect textRect)
  :_backgroundRect(backgroundRect), _email(nullptr), _pass(nullptr)
{
  SDL_Rect emailRect, passRect;

}

void SignIn::Update()
{

  _email->Update();
  _pass->Update();
}

void SignIn::CreateTextSquares(SDL_Rect& textRect)
{
  _email = new TextSquare({ textRect.x, textRect.y }, 1, LETTER_SIZE, 30);

  Vector2i passPos{ textRect.x,0 };
  passPos.y = _backgroundRect.y + _backgroundRect.h - (_backgroundRect.y  - textRect.y + LETTER_SIZE);
  //down of the background - margin between down email and and start of background 

  _pass = new TextSquare(passPos, 1, LETTER_SIZE, 30);
}

