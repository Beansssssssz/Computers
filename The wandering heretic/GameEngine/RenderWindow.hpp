#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Square.hpp"

class RenderWindow {
public:
  RenderWindow(const char* title);
  ~RenderWindow();
  SDL_Texture* LoadTexture(const char* filepath);
  void Render(Square sqr);
  void Render(Square* sqr);
  void CreateRect(SDL_Rect* rect, RGBA color);
  void Display();
  void Clear();
  void ToggleFullScreen();
  static void GetWidthHeight(int& width, int& height);
  bool IsWindowFocused();
  SDL_Window* GetWindow();
  SDL_Renderer* GetRenderer();

private:
  SDL_Window* window; //the window "tab" it self
  SDL_Renderer* renderer;//the way you communicate with the window :)

};
