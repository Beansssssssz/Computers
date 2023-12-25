#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <functional>


#include "Square.hpp"
#include "Math.hpp"
#include "Mouse.hpp"

class Button : public Square
{
public:
  Button(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect);
  ~Button();
  void Update(MouseButtons btn = MouseButtons::mbl);
  //void ChangeState(Mouse& mouse);
  bool GetIsSelected();
  bool GetIsPressed();
  bool GetIsReleased(MouseButtons state = MouseButtons::mbl);

  void SetIsSelected(bool val);
  void SetIsPressed(bool val);

private:
  bool _isSelected;
  bool _isPressed;

};
