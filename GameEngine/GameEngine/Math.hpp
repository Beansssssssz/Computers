#pragma once

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

struct RGBA
{
  RGBA()
    :r(0), g(0), b(0), a(0)
  {};
  RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    :r(r), g(g), b(b), a(a)
  {};
  Uint8 r, g, b, a;
};


