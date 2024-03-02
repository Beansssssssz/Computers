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

void GIF::RenderGIF(bool isRight) {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = _texs[_loc];

  window->FlipAndPrintTexture(tex, _src, _dst, !isRight);
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

SDL_Texture*& GIF::operator[](size_t index)
{
  return _texs[index];
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
}

//void GIF::FlipGif(GIF* gif, SDL_Rect srcRect, SDL_Rect dstRect)
//{
//  RenderWindow* win = RenderWindow::GetRenderWindowInstance();
//  SDL_Renderer* renderer = win->GetRenderer();
//
//  int length = gif->_len;
//  for (size_t i = 0; i < length; i++) {
//
//    SDL_Texture* newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, dstRect.w, dstRect.h);
//    if (!newTexture) {
//      SDL_LogError(SDL_LOG_CATEGORY_RENDER, "failed to create texture. SDL ERROR: %s", SDL_GetError());
//      continue; 
//    }
//
//    int ret = SDL_SetRenderTarget(renderer, newTexture);
//    if (ret != 0) {
//      SDL_LogError(SDL_LOG_CATEGORY_RENDER, "failed to set renderer target. SDL ERROR: %s", SDL_GetError());
//      SDL_DestroyTexture(newTexture);
//      continue;
//    }
//
//    ret = SDL_RenderCopyEx(renderer, (*gif)[i], &srcRect, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
//    if (ret != 0) {
//      SDL_LogError(SDL_LOG_CATEGORY_RENDER, "failed to copy texture. SDL ERROR: %s", SDL_GetError());
//      SDL_DestroyTexture(newTexture);
//      continue;
//    }
//
//    // Reset the rendering target to NULL
//    SDL_SetRenderTarget(renderer, nullptr);
//
//    SDL_DestroyTexture((*gif)[i]);
//    (*gif)[i] = newTexture;
//  }
//};
