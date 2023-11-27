#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title)
  :window(NULL), renderer(NULL)//sets the 2 vars to null
{
  int w, h;
  RenderWindow::GetWidthHeight(w, h);
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_FULLSCREEN);
  if (window == NULL)
    std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

  //the -1 is saying to use whatever flags the programs needs to run
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);                                                    
  if(renderer == NULL)
    std::cout << "Renderer failed to render. Error: " << SDL_GetError() << std::endl;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);//sets it so that you can blend colors
  ToggleFullScreen();
};

RenderWindow* RenderWindow::GetRenderWindow() {
  if (_windowPtr == NULL)
  {
    _windowPtr = new RenderWindow("Game");
    return _windowPtr;
  }
  else
    return _windowPtr;
}

/// <summary>
/// gets the path and turns it into a sdl texture
/// </summary>
/// <param name="filepath">thr path of an img to turn into an sdl_texture</param>
/// <returns>an sdl texture from the path</returns>
SDL_Texture* RenderWindow::LoadTexture(const char* filepath) {

  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(renderer, filepath);

  if (texture == NULL)
    std::cout << "Texture faild to load. Error: " << SDL_GetError() << std::endl;

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
void RenderWindow::Render(Square sqr)
{
  if (SDL_RenderCopy(renderer, sqr.GetTexture(), sqr.GetSrcRect(), sqr.GetDstRect()))
    std::cout << "1Texture faild to be copied. Error: " << SDL_GetError() << std::endl;
};
void RenderWindow::Render(Square* sqr)
{
  if (SDL_RenderCopy(renderer, sqr->GetTexture(), sqr->GetSrcRect(), sqr->GetDstRect()))
    std::cout << "1Texture faild to be copied. Error: " << SDL_GetError() << std::endl;
};


/// <summary>
/// not working currently.
/// </summary>
void RenderWindow::ToggleFullScreen()
{
  Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
  bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
  SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
}
void RenderWindow::GetWidthHeight(int& w, int& h)
{
  SDL_DisplayMode DM;
  SDL_GetDesktopDisplayMode(0, &DM);
  w = DM.w;
  h = DM.h;
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
  SDL_RenderClear(renderer);
};

RenderWindow::~RenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  delete _windowPtr;
};

SDL_Window* RenderWindow::GetWindow()
{
  return window;
};

SDL_Renderer* RenderWindow::GetRenderer()
{
  return renderer;
}
void RenderWindow::CreateRect(SDL_Rect* rect, RGBA color)
{
  RGBA oldColor;
  SDL_GetRenderDrawColor(renderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);

  //outline rect
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(renderer, rect);
  //fill up rectangle with color
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);

}
