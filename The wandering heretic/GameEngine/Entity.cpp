#include "Entity.hpp"

Entity::Entity(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :Entity::Square(tex, srcrect, dstrect),
  _isRight(true), _collisionEnabled(collisionEnabled)
{};

Entity::~Entity()
{};

bool Entity::CanMove(std::vector<Square*> vec, int offsetX, int offsetY) {
  SDL_Rect offsetRect{
    _dst.x + offsetX, _dst.y + offsetY,
    _dst.w, _dst.h
  };
  for(Square* sqr : vec)
    if (((Entity*)sqr)->_collisionEnabled && sqr->IsColliding(offsetRect))
      return false;

  return true;
}

bool Entity::GetIsRight()
{
  return _isRight;
}

void Entity::SetIsRight(bool isRight)
{
  _isRight = isRight;
}
