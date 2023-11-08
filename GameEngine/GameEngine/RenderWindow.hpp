#pragma once //cant get copied more than once
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow {
public:
  RenderWindow(const char* p_title, int p_width,int p_height);
private:
  SDL_Window* window; //the window "tab" it self(is a pointer)
  SDL_Renderer* renderer;//the way you communicate with the window

};
