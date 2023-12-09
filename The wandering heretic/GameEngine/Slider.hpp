#pragma once

#include "Square.hpp"

class Slider
{
public:
  Slider(SDL_Rect rect, int pos1, int pos2, RGBA color, int height);
  void Update();
  void CreateSliderPath();
  void MoveRectByMouse();
  int GetValue();

private:
  SDL_Rect _rect;
  Vector2i _oldPos;
  RGBA _color;

  int _pos1;
  int _pos2;
  int _height;

};
