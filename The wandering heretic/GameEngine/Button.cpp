#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Button.hpp"

Button::Button(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect)
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
  bool IsX = dstRect.x <= mouse->GetPos().x && (dstRect.x + dstRect.w >= mouse->GetPos().x);
  bool IsY = dstRect.y <= mouse->GetPos().y && (dstRect.y + dstRect.h >= mouse->GetPos().y);

  if (IsX && IsY) {
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
