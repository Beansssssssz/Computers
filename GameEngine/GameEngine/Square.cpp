#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Square.hpp"

Square::Square(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect, bool collisionEnabled)
  :tex(tex), srcRect(srcrect), dstRect(dstrect), collisionEnabled(collisionEnabled)
{}

Square::~Square()
{
}


bool Square::IsColliding(SDL_Rect& rect)
{
  if (!collisionEnabled)
    return false;
  bool top, bottom, left, right;

  top = dstRect.y <= rect.h + rect.y;

  //left = dstRect.x + dstRect.w >= rect.x;
  //bottom = dstRect.y + rect.h >= rect.y;
  //right = dstRect.y <= rect.y + rect.h;

  //if (top)
  //  return false;
  //else
  //{
  //std::cout << dstRect.y << std::endl;
  //std::cout << rect.y + rect.h << std::endl;
  //std::cout << "-----------------" << std::endl;
  //}
  //

  return top;
}

Vector2f& Square::GetPos()
{
  Vector2f pos(dstRect.x, dstRect.y);
  return pos;
}

SDL_Texture* Square::GetTexture()
{
  return tex;
}

SDL_Rect Square::GetDstRect()
{
  return dstRect;
}

SDL_Rect Square::GetSrcRect()
{
  return srcRect;
}
