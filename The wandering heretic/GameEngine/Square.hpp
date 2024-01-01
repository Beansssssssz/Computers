#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Math.hpp"

class Square {
public:
  Square(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, bool collisionEnabled = false);
  Square(std::string path, SDL_Rect src, SDL_Rect dst, bool collisionEnabled = false);

  ~Square();

  SDL_Texture* GetTexture();
  void SetTexture(const char* path, SDL_Rect src = { -1,-1,-1,-1 });

  std::string GetPath();
  SDL_Rect* GetSrcRect();
  SDL_Rect* GetDstRect();
  void SetSrcRect(SDL_Rect rect);
  void SetDstRect(SDL_Rect rect);

  bool IsColliding(SDL_Rect rect);
protected:
  SDL_Texture* _tex;
  std::string _path;

  SDL_Rect _src;
  SDL_Rect _dst;

  bool collisionEnabled = false;
};
