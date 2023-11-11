#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"


Entity::Entity(Vector2f pos, SDL_Texture* tex)
  :pos(pos), tex(tex)
{
  CurrentFrame.x = 0;
  CurrentFrame.y = 0;
  CurrentFrame.w = 32;
  CurrentFrame.h = 32;
};

Vector2f& Entity::GetPos() {
  return pos;
};

SDL_Texture* Entity::GetTexture()
{
  return tex;
};

SDL_Rect Entity::GetCurrentFrame()
{
  return CurrentFrame;
};

Entity::~Entity()
{};
