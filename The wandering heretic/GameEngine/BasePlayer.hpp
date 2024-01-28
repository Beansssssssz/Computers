#pragma once
#include "Entity.hpp"

enum class GifTypes
{
  idle,
  walking,
  running,
  attacking,
  death,
};

class BasePlayer : public Entity
{
public:
  BasePlayer(GIF** gifs, SDL_Rect srcrect, SDL_Rect dstrect, bool _collisionEnabled = true);
  ~BasePlayer();

  void Update() override;
private:
  //void ApplyGravity();
  void GetInput();

  GIF** _gifs;
};


