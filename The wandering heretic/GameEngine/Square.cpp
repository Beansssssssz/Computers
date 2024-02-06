#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Square.hpp"
#include "RenderWindow.hpp"

Square::Square(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool destroyTex)
  :_src(srcrect), _dst(dstrect), _tex(tex),
  _path(""), _destroytex(destroyTex)
{}

Square::Square(std::string path, SDL_Rect srcrect, SDL_Rect dstrect, bool destroyTex)
  :_path(path), _src(srcrect), _dst(dstrect),
  _tex(nullptr), _destroytex(destroyTex)
{
  if (path != "") {
    RenderWindow* window = RenderWindow::GetRenderWindowInstance();
    _tex = window->LoadTexture(path.c_str());
  }
}

Square::~Square()
{
  if (_tex != nullptr && _destroytex)
    SDL_DestroyTexture(_tex);
};

/// <summary>
/// return true if the rect provided and this rect are colliding.
/// </summary>
/// <param name="rect"></param>
/// <returns></returns>
bool Square::IsColliding(SDL_Rect rect)
{
  bool TopTobottom, BottomToTop, LeftToright, RightToleft;

  TopTobottom = _dst.y < rect.y + rect.h;
  LeftToright = _dst.x < rect.x + rect.h;
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
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_DestroyTexture(_tex);

  _path = path;
  _tex = window->LoadTexture(path);

  if (src.w == -1 && src.h == -1)//width and height cant be negetive
    _src = src;
};

/// <summary>
/// Returns the path of the Texture.
/// returns an empty string if there is no path
/// </summary>
/// <returns></returns>
std::string Square::GetPath()
{
  return _path;
};

/// <summary>
/// Sets the source rect of the rect to the provided rect.
/// </summary>
/// <param name="rect">SDL_Rect type</param>
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
