#include "GIF.hpp"

#include <iostream>

#include "RenderWindow.hpp"


GIF::GIF(SDL_Texture** texs, uint8_t len, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay)
  :_sqrs(nullptr), _len(len), _src(srcrect), _dst(dstrect),
  _delay(delay), _loc(0), _lastUpdatedTime(SDL_GetTicks())
{
  _sqrs = new Square*[len];

  for (uint8_t i = 0; i < len; i++)
    _sqrs[i] = new Square(texs[i], srcrect, dstrect);
}

GIF::GIF(const char* path, uint8_t len, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay)
  : _sqrs(nullptr), _len(len), _src(srcrect), _dst(dstrect),
  _delay(delay), _loc(0), _lastUpdatedTime(SDL_GetTicks())
{
  _sqrs = new Square * [len];

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  std::string Newpath;
  for (uint8_t i = 0; i < len; i++)
  {
    Newpath = path + std::to_string(i) + ".png";
    SDL_Texture* tex = window->LoadTexture(Newpath.c_str());
    _sqrs[i] = new Square(tex, srcrect, dstrect);
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
  //Square sqr(_texs[_loc], _src, _dst, false);
  window->Render(_sqrs[_loc]);
} 

Square* GIF::GetCurrentSquare()
{
  return _sqrs[_loc];
}
