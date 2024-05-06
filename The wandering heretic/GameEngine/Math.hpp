#pragma once

#include <SDL.h>

/// <summary>
/// has 2 variables
/// an float x
/// an float y
/// </summary>
struct Vector2f
{
  Vector2f()
    :x(0), y(0)
  {}
  Vector2f(float x, float y)
    :x(x), y(y)
  {}

  float x, y;
};

/// <summary>
/// has 2 variables
/// an int x
/// an int y
/// </summary>
struct Vector2i
{
  Vector2i()
    :x(0), y(0)
  {}
  Vector2i(int x, int y)
    :x(x), y(y)
  {}

  int x, y;
};
