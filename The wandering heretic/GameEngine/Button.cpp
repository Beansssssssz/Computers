#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Button.hpp"

Button::Button(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect)
:Button::Square(tex, srcrect, dstrect), isPressed(false), isSelected(false)
{
  isSelected = false;
};

Button::~Button()
{};

void Button::Update(MouseButtons btn)
{
  Mouse* mouse = Mouse::GetMouse();

  isPressed = false;
  isSelected = false;
  //bool IsX = dst.x <= mouse->GetPos().x && (dst.x + dst.w >= mouse->GetPos().x);
  //bool IsY = dst.y <= mouse->GetPos().y && (dst.y + dst.h >= mouse->GetPos().y);

  //if (IsX && IsY) {
  //  isSelected = true;
  //  if (mouse->GetPressed() == btn)
  //    isPressed = true;
  //}

  if (mouse->IsMouseColliding(dst)) {
    isSelected = true;
    if (mouse->GetPressed() == btn)
      isPressed = true;
  }

  if (isSelected)
    mouse->MouseIsSelecting();
};

bool Button::GetIsSelected()
{
  return isSelected;
};

bool Button::GetIsPressed()
{
  return isPressed;
};
