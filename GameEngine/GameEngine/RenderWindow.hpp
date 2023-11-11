#pragma once //cant get copied more than once
#include <SDL.h>
#include <SDL_image.h>

//#include "Entity.hpp"
#include "Square.hpp"


class RenderWindow {
public:
  RenderWindow(const char* title, int width,int height);
  SDL_Texture* LoadTexture(const char* filepath);
  void Display();
  void Render(Square& entity);
  void Clear();
  ~RenderWindow();
private:
  SDL_Window* window; //the window "tab" it self(is a pointer)
  SDL_Renderer* renderer;//the way you communicate with the window :)   

};
