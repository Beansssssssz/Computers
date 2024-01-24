#pragma once
#include "Square.hpp"

#include <vector>

class Entity :public Square
{
public:
  Entity(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool _collisionEnabled = true);
  ~Entity();
  bool CanMove(std::vector<Square*> vec, int offsetX, int offsetY);
  bool GetIsRight();
  void SetIsRight(bool isRight);
  
private:
  bool _isRight;
  bool _collisionEnabled;
};
