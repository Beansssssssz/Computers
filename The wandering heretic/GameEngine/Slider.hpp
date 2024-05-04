#pragma once

#include "Square.hpp"

class Slider
{
public:
  Slider(SDL_Rect rect, int minSliderPos, int maxSliderPos, SDL_Color color, int height);
  void Update();
  void CreateSliderPath();
  void MoveRectByMouse();

  int GetValue();
  SDL_Rect GetRect();

private:
  SDL_Rect _rect; //the slider button
  Vector2i _oldPos;
  SDL_Color _color; //the slider color

  int _min;
  int _max;
  int _height;

};
