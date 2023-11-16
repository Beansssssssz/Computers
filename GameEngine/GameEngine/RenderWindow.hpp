#pragma once //cant get copied more than once
#include <SDL.h>
#include <SDL_image.h>

#include "Square.hpp"


class RenderWindow {
public:
  RenderWindow(const char* title, int width,int height);
  ~RenderWindow();
  SDL_Texture* LoadTexture(const char* filepath);
  void Display();
  void Render(SDL_Texture* tex, SDL_Rect dstrect, SDL_Rect srcrect);
  void Clear();
  void ToggleFullScreen();
  SDL_Window* GetWindow();
  SDL_Renderer* GetRenderer();
private:
  SDL_Window* window; //the window "tab" it self
  SDL_Renderer* renderer;//the way you communicate with the window :) 
};
