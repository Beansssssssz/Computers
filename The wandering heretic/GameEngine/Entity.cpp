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
  if (_gif != nullptr) {
    delete _gif;
    _gif = nullptr;
  }
};

/// <summary>
/// if the gif isnt null then it renders the current state gif
/// and checks what png to currenly displaye
/// and updates the gif position in the world
/// </summary>
void Entity::Update()
{
  if (_gif != nullptr) {
    _gif->SetDstRect(_dst);
    _gif->Update();
    _gif->RenderGIF(_isRight);
  }
}

/// <summary>
/// moves the dst to the desired loc
/// return true if the entity moved said offset
/// otherwise returns false
/// </summary>
/// <param name="offsetX:"> the amount to change in the x axis</param>
/// <param name="offsetY:"> the amount to change in the y axis</param>
/// <returns>true if the value did change. otherwise returns false</returns>
bool Entity::MoveTo(std::vector<Entity*> vec, int8_t offsetX, int8_t offsetY, bool snap) {
  if (offsetX == 0 && offsetY == 0)
    return true;

  SDL_Rect newDst = _dst;
  newDst.x += offsetX;
  newDst.y += offsetY;

  for (Entity* sqr : vec)
    if (sqr->_collisionEnabled && sqr->IsColliding(newDst)) {
      if (snap)
        SnapToRect(*sqr->GetDstRect(), offsetX, offsetY);
      
      return false;
    }

  _dst = newDst;
  return true;
}

/// <summary>
/// snapes the entity into the inputed rect
/// using the offsetX and offsetY var to find out where to snap
/// </summary>
/// <param name="rect"></param>
/// <param name="offsetX"></param>
/// <param name="offsetY"></param>
void Entity::SnapToRect(SDL_Rect rect, int8_t offsetX, int8_t offsetY)
{
  if (offsetX > 0) //snap to left
    _dst.x = rect.x - _dst.w;

  else if (offsetX < 0) //snap to right
    _dst.x = rect.x + rect.w;

  if (offsetY > 0) //snap to top
    _dst.y = rect.y - _dst.h;

  else if (offsetY < 0) //snap to down
    _dst.y = rect.y + rect.h;
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
