#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Square
{
public:
  Square(Vector2f pos, SDL_Texture* tex, SDL_Rect& rect);
  ~Square();
  Vector2f& GetPos();
  SDL_Texture* GetTexture();
  SDL_Rect GetRect();
protected:
  SDL_Texture* tex;
  SDL_Rect rect;
  Vector2f pos;
};
