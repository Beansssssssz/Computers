#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

Entity::Entity(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect)
  :Entity::Square(tex, srcrect, dstrect), IsRight(false)
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
