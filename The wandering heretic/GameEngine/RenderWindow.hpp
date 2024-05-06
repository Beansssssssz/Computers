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

  SDL_Renderer* GetRenderer();

  void FlipAndPrintTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, bool flip);

  /* in order for other parts or the code to know whether or no
     the settings is open so i save it in this static class */
  static bool GLOBAL_SETTING_OPEN;

private:
  RenderWindow(const char* title);
  static RenderWindow* _windowPtr;

  SDL_Window* window; //the window "tab" it self
  SDL_Renderer* renderer;//the way you communicate with the window
};

