#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

class Platforms : Entity
{
public:
  //Platforms(Vector2f vec, SDL_Texture* tex);
  //~Platforms();
  bool Collision(Vector2f vec);

private:

};
