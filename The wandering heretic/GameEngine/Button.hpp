#pragma once 
#include <SDL.h>
#include <SDL_image.h>


#include "Square.hpp"
#include "Math.hpp"
#include "Mouse.hpp"

class Button : public Square
{
public:
  Button(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect);
  ~Button();
  static Button CreateButton(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect);
  void Update(Mouse& mouse, MouseButtons btn);
  //void ChangeState(Mouse& mouse);
  bool GetIsSelected();
  bool GetIsPressed();
private:
  bool isSelected;
  bool isPressed;

};
