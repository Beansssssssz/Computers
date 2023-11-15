#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Square.hpp"

class Entity :Square
{
public:
  Entity(Vector2f pos, SDL_Texture* tex, SDL_Rect& rect);
  ~Entity();
  bool GetIsRight();
  void SetIsRight(bool isRight);
  bool IsColliding(SDL_Rect& rect);
  
private:
  bool IsRight;


};
