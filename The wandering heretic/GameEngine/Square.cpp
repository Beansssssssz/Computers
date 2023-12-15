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
  SDL_DestroyTexture(tex);
}

/// <summary>
/// return true if the rect provided and this rect are colliding.
/// </summary>
/// <param name="rect"></param>
/// <returns></returns>
bool Square::IsColliding(SDL_Rect rect)
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

/// <summary>
/// returns texture of the rect
/// </summary>
/// <returns></returns>
SDL_Texture* Square::GetTexture()
{
  return tex;
}

/// <summary>
/// sets the texture of the rect to the provided texture
/// </summary>
/// <param name="texture"></param>
void Square::SetTexture(SDL_Texture* texture)
{
  tex = texture;
};

/// <summary>
/// sets the source rect of the rect to the provided rect
/// </summary>
/// <param name="rect"></param>
void Square::SetSrcRect(SDL_Rect rect)
{
  src = rect;
}

/// <summary>
/// sets the dest rect of the rect to the provided rect
/// </summary>
/// <param name="rect"></param>
void Square::SetDstRect(SDL_Rect rect)
{
  dst = rect;
};

/// <summary>
/// returns the source rect
/// </summary>
/// <returns></returns>
SDL_Rect* Square::GetSrcRect()
{
  return &src;
};

/// <summary>
/// returns the dest rect
/// </summary>
/// <returns></returns>
SDL_Rect* Square::GetDstRect()
{
  return &dst;
};
