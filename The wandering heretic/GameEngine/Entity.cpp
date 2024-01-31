#include "Entity.hpp"

#include <iostream>

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
  :Entity::Square("", srcrect, dstrect),  _gif(gif),
  _isRight(true), _collisionEnabled(collisionEnabled)
{};

Entity::~Entity()
{
  delete _gif;
  _gif = nullptr;
};

/// <summary>
/// Updates all the nececery data for the entity
/// </summary>
void Entity::Update()
{
  if (_gif != nullptr) {
    _gif->SetDstRect(_dst);
    _gif->Update();
    _gif->RenderGIF();
  }
}

/// <summary>
/// TODO
/// </summary>
/// <param name="vec">/param>
/// <param name="offsetX"></param>
/// <param name="offsetY"></param>
void Entity::MoveTo(std::vector<Entity*> vec, int8_t offsetX, int8_t offsetY) {
  SDL_Rect newDst = _dst;
  newDst.x += offsetX;
  newDst.y += offsetY;

  for (Entity* sqr : vec)
    if (sqr != nullptr && sqr->_collisionEnabled && sqr->IsColliding(newDst))
      return;
  _dst = newDst;
}

GIF* Entity::GetGIF()
{
    return _gif;
}

/// <summary>
/// deletese the original gif
/// </summary>
/// <param name="gif"></param>
void Entity::SetGIF(GIF* gif)
{
  delete _gif;
  _gif = gif;
}

bool Entity::GetIsRight()
{
  return _isRight;
}

void Entity::SetIsRight(bool isRight)
{
  _isRight = isRight;
}
