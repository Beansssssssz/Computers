#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Square.hpp"
#include "RenderWindow.hpp"


Square::Square(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :tex(tex), src(srcrect), dst(dstrect), collisionEnabled(collisionEnabled)
{}

Square::~Square()
{
}


bool Square::IsColliding(SDL_Rect& rect)
{
  if (!collisionEnabled)
    return false;
  bool TopTobottom, BottomToTop, LeftToright, RightToleft;

  TopTobottom = dst.y <= rect.y + rect.h;//
  LeftToright = dst.x < rect.x + rect.h;//
  BottomToTop = dst.y + dst.h > rect.y;
  RightToleft = dst.x + dst.w > rect.x;

  return TopTobottom && BottomToTop && LeftToright && RightToleft;
}

SDL_Texture* Square::GetTexture()
{
  return tex;
}

void Square::SetTexture(SDL_Texture* texture)
{
  tex = texture;
};

void Square::SetSrcRect(SDL_Rect rect)
{
  src = rect;
}
void Square::SetDstRect(SDL_Rect rect)
{
  dst = rect;
};

SDL_Rect* Square::GetSrcRect()
{
  return &src;
};

SDL_Rect* Square::GetDstRect()
{
  return &dst;
};
