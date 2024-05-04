#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Button.hpp"

Button::Button(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool deleteTex)
  :Button::Square(tex, srcrect, dstrect, deleteTex), _isPressed(false), _isSelected(false)
  {}

Button::Button(std::string path, SDL_Rect srcrect, SDL_Rect dstrect, bool deleteTex)
  :Button::Square(path, srcrect, dstrect, deleteTex), _isPressed(true), _isSelected(false)
  {}

Button::~Button()
{
  Square::~Square();
};

/// <summary>
/// checks if the button was pressed by mouse using the
/// mouse button specified. if settings is open then the button
/// just ignore the mouse entirely
/// </summary>
/// <param name="btn"></param>
/// <param name="settingOpen"></param>
void Button::Update(MouseButtons btn, bool settingOpen)
{
  Mouse* mouse = Mouse::GetMouseInstance();

  _isPressed = false;
  _isSelected = false;

  if (mouse->IsMouseColliding(_dst) && !settingOpen) {
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
