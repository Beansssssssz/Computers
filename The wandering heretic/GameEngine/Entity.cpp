#include "Entity.hpp"

Entity::Entity(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :Entity::Square(tex, srcrect, dstrect), _gif(nullptr),
  _isRight(true), _collisionEnabled(collisionEnabled)
{
}

Entity::Entity(std::string path, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :Entity::Square(path, srcrect, dstrect), _gif(nullptr),
  _isRight(true), _collisionEnabled(collisionEnabled)
{
}

Entity::Entity(GIF* gif, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :Entity::Square("", srcrect, dstrect), _gif(gif),
  _isRight(true), _collisionEnabled(collisionEnabled)
{};

Entity::~Entity()
{};

/// <summary>
/// Updates all the nececery data for the entity
/// </summary>
void Entity::Update()
{
  if (_gif != nullptr)
    _gif->Update();
}

/// <summary>
/// TODO
/// </summary>
/// <param name="vec">the vector of all the list</param>
/// <param name="offsetX"></param>
/// <param name="offsetY"></param>
void Entity::MoveTo(std::vector<Square*> vec, int offsetX, int offsetY) {
  SDL_Rect offsetRect{
    _dst.x + offsetX, _dst.y + offsetY,
    _dst.w, _dst.h
  };
  for (Square* sqr : vec)
    if (((Entity*)sqr)->_collisionEnabled && sqr->IsColliding(offsetRect))
      break;

}

bool Entity::GetIsRight()
{
  return _isRight;
}

void Entity::SetIsRight(bool isRight)
{
  _isRight = isRight;
}
