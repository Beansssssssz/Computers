#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Button.hpp"

Button::Button(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect)
  :Button::Square(tex, srcrect, dstrect), _isPressed(false), _isSelected(false)
{
  _isSelected = false;
};

Button::~Button()
{};

void Button::Update(MouseButtons btn)
{
  Mouse* mouse = Mouse::GetMouse();

  _isPressed = false;
  _isSelected = false;
  //bool IsX = dst.x <= mouse->GetPos().x && (dst.x + dst.w >= mouse->GetPos().x);
  //bool IsY = dst.y <= mouse->GetPos().y && (dst.y + dst.h >= mouse->GetPos().y);

  //if (IsX && IsY) {
  //  _isSelected = true;
  //  if (mouse->GetPressed() == btn)
  //    _isPressed = true;
  //}

  if (mouse->IsMouseColliding(dst)) {
    _isSelected = true;
    if (mouse->GetPressed() == btn) 
      _isPressed = true;
  }

  if (_isSelected)
    mouse->MouseIsSelecting();
};

bool Button::GetIsSelected()
{
  return _isSelected;
};

bool Button::GetIsPressed()
{
  return _isPressed;
}

void Button::SetIsSelected(bool val)
{
   _isSelected = val;
};

void Button::SetIsPressed(bool val)
{
  _isPressed = val;
};
