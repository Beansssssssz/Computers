#pragma once

#include "Entity.hpp"
class BasePlayer : public Entity
{
public:
  BasePlayer(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool _collisionEnabled = true);
  ~BasePlayer();

  void Update();
private:
  //void ApplyGravity();
  void GetInput();

};

