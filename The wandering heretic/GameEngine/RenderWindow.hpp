#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Square.hpp"

class RenderWindow {
public:
  static RenderWindow* GetRenderWindowInstance();
  ~RenderWindow();

  SDL_Texture* LoadTexture(const char* filepath);
  void DisplayRect(SDL_Rect* rect, SDL_Color color);

  void Render(Square* sqr);
  void Display();
  void Clear();

  static void GetWidthHeight(int& width, int& height);
  bool IsWindowFocused();

  SDL_Window* GetWindow();
  SDL_Renderer* GetRenderer();

  void FlipAndPrintTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, bool flip);
private:
  RenderWindow(const char* title);
  static RenderWindow* _windowPtr;

  SDL_Window* window; //the window "tab" it self
  SDL_Renderer* renderer;//the way you communicate with the window :)

};
