#pragma once 
#include <SDL.h>
#include <SDL_image.h>


#include "Square.hpp"
#include "Math.hpp"
#include "Mouse.hpp"

class Button : public Square
{
public:
  Button(Vector2f pos, SDL_Texture* tex, SDL_Rect& rect);
  ~Button();
  void Update(Mouse& mouse);
  void ChangeState();
  bool GetIsSelected();
  bool GetIsPressed();

private:
  bool isSelected;
  bool isPressed;

};
