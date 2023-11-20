#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Square.hpp"


class RenderWindow {
public:
  RenderWindow(const char* title, int width,int height);
  ~RenderWindow();
  SDL_Texture* LoadTexture(const char* filepath);
  void Render(SDL_Texture* tex, SDL_Rect* srcrect, SDL_Rect dstrect); 
  void CreateRect(SDL_Rect* rect, RGBA color);
  void Display();
  void Clear();
  void ToggleFullScreen();
  SDL_Window* GetWindow();
  SDL_Renderer* GetRenderer();
private:
  SDL_Window* window; //the window "tab" it self
  SDL_Renderer* renderer;//the way you communicate with the window :)

};
