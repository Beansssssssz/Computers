#pragma once 
#include <SDL.h>
#include <SDL_image.h>

#include "Square.hpp"
#include "Math.hpp"

enum class ButtonPressed {
  none = 0,
  mbl = 1,
  mbm = 2,
  mbr = 4,
  mb4 = 8,
  mb5 = 16
};

class Mouse
{
public:
  Mouse(Vector2i pos);
  ~Mouse();
  Vector2i GetPos();
  ButtonPressed GetPressed();
  void UpdatePos();

private:
  ButtonPressed bt = ButtonPressed::none;
  Vector2i pos;
  SDL_Cursor* cursor;
};
