#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* tex, SDL_Rect& rect)
  :Entity::Square(pos, tex, rect)
{
}

Entity::~Entity()
{
}

bool Entity::GetIsRight()
{
  return IsRight;
}

void Entity::SetIsRight(bool isRight)
{
  IsRight = isRight;
}

bool Entity::IsColliding(SDL_Rect& rect)
{
  return false;
}
