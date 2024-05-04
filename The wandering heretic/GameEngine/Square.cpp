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
    _destroytex = destroyTex;
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
  return SDL_HasIntersection(&_dst, &rect);
}

SDL_Texture* Square::GetTexture()
{
  return _tex;
}

void Square::SetTexture(const char* path, SDL_Rect src)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_DestroyTexture(_tex);

  _path = path;
  _tex = window->LoadTexture(path);

  if (src.w != -1 && src.h != -1)
    _src = src;
}

void Square::SetTexture(SDL_Texture* tex, SDL_Rect src)
{
  SDL_DestroyTexture(_tex);
  _path = "";
  _tex = tex;

  if (src.w != -1 && src.h != -1)
    _src = src;
};

std::string Square::GetPath()
{
  return _path;
};

void Square::SetSrcRect(SDL_Rect rect)
{
  _src = rect;
}

void Square::SetDstRect(SDL_Rect rect)
{
  _dst = rect;
};

SDL_Rect* Square::GetSrcRect()
{
  return &_src;
};

SDL_Rect* Square::GetDstRect()
{
  return &_dst;
};
