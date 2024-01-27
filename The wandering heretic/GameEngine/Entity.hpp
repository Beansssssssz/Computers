#pragma once
#include "Square.hpp"
#include "GIF.hpp"

#include <vector>

class Entity :public Square
{
public:
  Entity(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled = true);
  Entity(std::string path, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled = true);
  Entity(GIF* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled = true);
  ~Entity();

  void Update();
  void MoveTo(std::vector<Square*> vec, int offsetX, int offsetY);

  bool GetIsRight();
  void SetIsRight(bool isRight);

private:
  GIF* _gif;
  bool _isRight;
  bool _collisionEnabled;
};
