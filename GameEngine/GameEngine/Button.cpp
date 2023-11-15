#include <SDL.h>
#include <SDL_image.h>

#include "Button.hpp"

Button::Button(Vector2f pos, SDL_Texture* tex, SDL_Rect& rect)
  :Button::Square(pos, tex, rect), isPressed(false), isSelected(false)
{
  isSelected = false;
}

Button::~Button()
{
}

void Button::Update(Mouse& mouse, ButtonPressed btn = ButtonPressed::mbl)
{
  isPressed = false;
  isSelected = false;
  bool IsX = pos.x < mouse.GetPos().x && (pos.x + rect.w > mouse.GetPos().x);
  bool IsY = pos.y < mouse.GetPos().y && (pos.y + rect.h > mouse.GetPos().y);
  if (IsX && IsY) {
    isSelected = true;
    if (mouse.GetPressed() == btn)
      isPressed = true;
  }

  if (isSelected)
    ChangeState(mouse);
}

void Button::ChangeState(Mouse& mouse) {

}

bool Button::GetIsSelected()
{
  return isSelected;
}

bool Button::GetIsPressed()
{
  return isPressed;
}

