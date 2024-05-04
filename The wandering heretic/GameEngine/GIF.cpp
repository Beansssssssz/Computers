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

/// <summary>
/// checks which texture to currenly display using
/// the len var inputed in the build
/// </summary>
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

/// <summary>
/// renders the gif based on if he is right or left
/// </summary>
/// <param name="isRight"></param>
void GIF::RenderGIF(bool isRight) {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = _texs[_loc];

  window->FlipAndPrintTexture(tex, _src, _dst, !isRight);
}

/// <summary>
/// makes the gif into a type of array
/// when using the [] on hime it returns the corresponding
/// texture in the array
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
SDL_Texture*& GIF::operator[](size_t index)
{
  return _texs[index];
}

SDL_Rect* GIF::GetDstRect()
{
  return &_dst;
}

SDL_Rect* GIF::GetSrcRect()
{
  return &_src;
}

void GIF::SetDstRect(SDL_Rect rect)
{
  _dst = rect;
};

void GIF::SetSrcRect(SDL_Rect rect)
{
  _src = rect;
}

uint8_t GIF::GetTextureCount()
{
    return _len;
}

uint8_t GIF::GetCurrentTexCount()
{
  return _loc;
}
