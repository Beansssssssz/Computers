#pragma once

struct Vector2f
{
  Vector2f()
    :x(0), y(0), velocityX(0), velocityY(0)
  {}
  Vector2f(float x, float y)
    :x(x), y(y), velocityX(0), velocityY(0)
  {}
  Vector2f(float x, float y, float Xv, float Yv)
    :x(x), y(y), velocityX(Xv), velocityY(Yv)
  {}

  float x, y;
  float velocityX, velocityY;
};

