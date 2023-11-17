#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Square.hpp"

class Entity :public Square
{
public:
  Entity(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect);
  ~Entity();
  bool GetIsRight();
  void SetIsRight(bool isRight);
  
private:
  bool IsRight;
};
