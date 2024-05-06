#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Math.hpp"

class Square {
public:
  Square(SDL_Texture* tex, SDL_Rect srcrect, SDL_Rect dstrect, bool destroyTex = true);
  Square(std::string path, SDL_Rect srcrect, SDL_Rect dstrect, bool destroyTex = true);

  virtual ~Square();

  virtual SDL_Texture* GetTexture();
  void SetTexture(const char* path, SDL_Rect src = { -1,-1,-1,-1 });
  void SetTexture(SDL_Texture* tex, SDL_Rect src = { -1,-1,-1,-1 });
  std::string GetPath();

  SDL_Rect* GetSrcRect();
  SDL_Rect* GetDstRect();
  void SetSrcRect(SDL_Rect rect);
  void SetDstRect(SDL_Rect rect);

  bool IsColliding(SDL_Rect rect);
protected:
  SDL_Texture* _tex; //the texture itself
  std::string _path; //the path to the texture(can be none)

  SDL_Rect _src; //where from the texture to take the buffer from
  SDL_Rect _dst; //where to print out the texture taken using the src

  //a bool variable that saves whether or not to delete the texture when class is deleted
  bool _destroytex;
};
