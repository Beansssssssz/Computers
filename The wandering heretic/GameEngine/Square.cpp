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
  bool TopTobottom, BottomToTop, LeftToright, RightToleft;

  TopTobottom = dstRect.y <= rect.y + rect.h;//

  LeftToright = dstRect.x < rect.x + rect.h;//

  BottomToTop = dstRect.y + dstRect.h > rect.y;

  RightToleft = dstRect.x + dstRect.w > rect.x;

  //std::cout << dstRect.x << ", " << rect.x + rect.h << "\n";
  //std::cout << LeftToright << std::endl;

  return TopTobottom && BottomToTop && LeftToright && RightToleft;
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

void Square::SetTexture(SDL_Texture* texture)
{
  tex = texture;
};

SDL_Rect Square::GetDstRect()
{
  return dstRect;
}

SDL_Rect* Square::GetSrcRect()
{
  return &srcRect;
}
