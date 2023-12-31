#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Square.hpp"
#include "RenderWindow.hpp"

Square::Square(const char* path, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :_path(path), _src(srcrect), _dst(dstrect), collisionEnabled(collisionEnabled)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  _tex = window->LoadTexture(path);
}

Square::Square(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool collisionEnabled)
  :_path(NULL), _src(srcrect), _dst(dstrect),
  collisionEnabled(collisionEnabled), _tex(tex)
{}

Square::~Square()
{
  if(_tex != NULL)
    SDL_DestroyTexture(_tex);
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

  TopTobottom = _dst.y <= rect.y + rect.h;//
  LeftToright = _dst.x < rect.x + rect.h;//
  BottomToTop = _dst.y + _dst.h > rect.y;
  RightToleft = _dst.x + _dst.w > rect.x;

  return TopTobottom && BottomToTop && LeftToright && RightToleft;
}

/// <summary>
/// returns texture of the rect
/// </summary>
/// <returns></returns>
SDL_Texture* Square::GetTexture()
{
  return _tex;
}

/// <summary>
/// sets the texture of the rect to the provided texture
/// if u want the src rect to stay the then dont input the src param
/// </summary>
/// <param name="texture"></param>
void Square::SetTexture(const char* path, SDL_Rect src)
{
  _path = path;
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  _tex = window->LoadTexture(path);

  if (src.w == -1 && src.h == -1)//width and height cant be negetive
    _src = src;
};

/// <summary>
/// sets the source rect of the rect to the provided rect
/// </summary>
/// <param name="rect"></param>
void Square::SetSrcRect(SDL_Rect rect)
{
  _src = rect;
}

/// <summary>
/// sets the dest rect of the rect to the provided rect
/// </summary>
/// <param name="rect"></param>
void Square::SetDstRect(SDL_Rect rect)
{
  _dst = rect;
};

/// <summary>
/// returns the source rect
/// </summary>
/// <returns></returns>
SDL_Rect* Square::GetSrcRect()
{
  return &_src;
};

/// <summary>
/// returns the dest rect
/// </summary>
/// <returns></returns>
SDL_Rect* Square::GetDstRect()
{
  return &_dst;
};
