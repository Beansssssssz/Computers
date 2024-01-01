#include "RenderWindow.hpp"

#include <iostream>

RenderWindow::RenderWindow(const char* title)
  :window(NULL), renderer(NULL)
{
  int w, h;
  RenderWindow::GetWidthHeight(w, h);

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_FULLSCREEN);

  if (window == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window failed to init.Error: % s", SDL_GetError());

  //the -1 is saying to use whatever flags the programs needs to run
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);

  if(renderer == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer failed to render. Error: %s", SDL_GetError());

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);//sets it so that you can blend colors
  //ToggleFullScreen();
};

RenderWindow::~RenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
};

RenderWindow* RenderWindow::GetRenderWindowInstance() {
  if (_windowPtr == NULL)
    _windowPtr = new RenderWindow("Game");
  return _windowPtr;
}

/// <summary>
/// gets the path and turns it into a sdl texture
/// </summary>
/// <param name="filepath">thr path of an img to turn into an sdl_texture</param>
/// <returns>an sdl texture from the path</returns>
SDL_Texture* RenderWindow::LoadTexture(const char* filepath) {
   SDL_Texture* texture = IMG_LoadTexture(renderer, filepath);
  if (texture == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture faild to load. Error: %s", IMG_GetError());

  return texture;
};

/// <summary>
/// copies the the renderer buffer into the screen buffer
/// </summary>
void RenderWindow::Display() {
  SDL_RenderPresent(renderer);
};

/// <summary>
/// copies the texture onto the renderer
/// </summary>
/// <param name="sqr">the root class sqaure</param>
void RenderWindow::Render(Square* sqr)
{
  if (SDL_RenderCopy(renderer, sqr->GetTexture(), sqr->GetSrcRect(), sqr->GetDstRect()))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture faild to be copied. Error: %s"
      , SDL_GetError());
};

void RenderWindow::GetWidthHeight(int& w, int& h)
{
  w = 1920;
  h = 1080;
};

bool RenderWindow::IsWindowFocused()
{
  Uint32 flags = SDL_GetWindowFlags(window);
  return flags & SDL_WINDOW_INPUT_FOCUS;
};

/// <summary>
/// clears the screen buffer
/// </summary>
void RenderWindow::Clear() {
  if(SDL_RenderClear(renderer) != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Failed to clean renderer");
};

SDL_Window* RenderWindow::GetWindow()
{
  return window;
};

SDL_Renderer* RenderWindow::GetRenderer()
{
  return renderer;
};

void RenderWindow::DisplayRect(SDL_Rect* rect, SDL_Color color)
{
  SDL_Color oldColor;
  int err = SDL_GetRenderDrawColor(renderer, &oldColor.r,
    &oldColor.g, &oldColor.b, &oldColor.a);

  //outline rect
  err += SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  err += SDL_RenderDrawRect(renderer, rect);
  err += SDL_RenderFillRect(renderer, rect);

  err += SDL_SetRenderDrawColor(renderer, oldColor.r,
    oldColor.g, oldColor.b, oldColor.a);

  if (err != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Sdl failed to render a rect %s", SDL_GetError());
}
