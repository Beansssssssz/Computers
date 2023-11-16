#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Square.hpp"

Square::Square(SDL_Texture* tex, SDL_Rect& srcrect, SDL_Rect& dstrect)
  :tex(tex), srcRect(srcrect), dstRect(dstrect)
{}

Square::~Square()
{
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
