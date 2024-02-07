#include "GIF.hpp"

#include <iostream>

#include "RenderWindow.hpp"


GIF::GIF(SDL_Texture** texs, uint8_t len, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay)
  :_texs(nullptr), _len(len), _src(srcrect), _dst(dstrect),
  _delay(delay), _loc(0), _lastUpdatedTime(SDL_GetTicks())
{
  _texs = texs;
}

GIF::GIF(const char* path, uint8_t len, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay)
  : _texs(nullptr), _len(len), _src(srcrect), _dst(dstrect),
  _delay(delay), _loc(0), _lastUpdatedTime(SDL_GetTicks())
{
  _texs = new SDL_Texture * [len];

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  std::string Newpath;
  for (uint8_t i = 0; i < len; i++)
  {
    Newpath = path + std::to_string(i) + ".png";
    _texs[i] = window->LoadTexture(Newpath.c_str());
  }
}

void GIF::Update()
{
  uint32_t current = SDL_GetTicks();

  if (_lastUpdatedTime + _delay <= current) {
    _lastUpdatedTime = current;
    _loc++;
    if (_loc >= _len)
      _loc = 0;
  }
}

void GIF::RenderGIF() {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Square sqr(_texs[_loc], _src, _dst, false);
  window->Render(&sqr);
}

SDL_Texture* GIF::GetCurrentTexture()
{
  return _texs[_loc];
}

void GIF::SetCurrentTexture(SDL_Texture* tex, uint8_t loc)
{
  SDL_DestroyTexture(_texs[loc]);
  _texs[loc] = tex;
}

SDL_Rect GIF::GetDstRect()
{
  return _dst;
}

SDL_Rect GIF::GetSrcRect()
{
  return _src;
}

void GIF::SetDstRect(SDL_Rect rect)
{
  _dst = rect;
};

void GIF::SetSrcRect(SDL_Rect rect)
{
  _src = rect;
};
