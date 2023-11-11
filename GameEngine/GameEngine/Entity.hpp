#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
  Entity(Vector2f vec, SDL_Texture* tex);
  ~Entity();
  Vector2f& GetPos();
  SDL_Texture* GetTexture();
  SDL_Rect GetCurrentFrame();
private:
  Vector2f pos;
  SDL_Rect CurrentFrame;
  SDL_Texture* tex;
};
