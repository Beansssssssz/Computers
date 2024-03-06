#pragma once

#include <SDL.h>
#include<SDL_image.h>

#include "Square.hpp"

class GIF
{
public:
  GIF(SDL_Texture** texs, uint8_t len, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay);
  GIF(const char* path, uint8_t len, SDL_Rect srcrect, SDL_Rect dstrect, uint16_t delay);

  void Update();
  void RenderGIF(bool isRight);

  SDL_Texture* GetCurrentTexture();
  void SetCurrentTexture(SDL_Texture* tex, uint8_t loc);
  _NODISCARD SDL_Texture*& operator[](size_t index);

  SDL_Rect GetDstRect();
  SDL_Rect GetSrcRect();

  void SetDstRect(SDL_Rect rect);
  void SetSrcRect(SDL_Rect rect);
private:
  SDL_Texture** _texs; //pointer arrays of the pngs
  uint8_t _loc; //the current iterator of the tex array

  uint8_t _len; //the length of the array.
  SDL_Rect _src;
  SDL_Rect _dst;
  uint16_t _delay; //The delay time in ms.

  uint32_t _lastUpdatedTime; //The current time
};

