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
  Mouse* mouse = Mouse::GetMouseInstance();

  _isPressed = false;
  _isSelected = false;

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
};

/// <summary>
/// returns whether or not
/// </summary>
/// <returns></returns>
bool Button::GetIsReleased(MouseButtons state)
{
  Mouse* mouse = Mouse::GetMouseInstance();
  return _isPressed && mouse->GetPressed() != state;
};

void Button::SetIsSelected(bool val)
{
   _isSelected = val;
};

void Button::SetIsPressed(bool val)
{
  _isPressed = val;
};
