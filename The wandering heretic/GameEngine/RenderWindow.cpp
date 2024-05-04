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

  const SDL_Rect SetSize = { 0, 0, 1920, 1080 };//the size i render the game(its a fixed size)
  if(SDL_RenderSetViewport(renderer, &SetSize) != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to set Viewport. Error: %s", SDL_GetError());
};

RenderWindow::~RenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
};

/// <summary>
/// returns the instance to the static object of this class
/// this is the only way to get an object of this class
/// this always returns the same object
/// </summary>
/// <returns></returns>
RenderWindow* RenderWindow::GetRenderWindowInstance() {
  if (_windowPtr == nullptr)
    _windowPtr = new RenderWindow("Game");
  return _windowPtr;
}

/// <summary>
/// gets the path and turns it into a sdl texture
/// </summary>
/// <param name="filepath">the path of an image to turn into an sdl_texture</param>
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
/// copies the texture onto the renderer buffer
/// </summary>
/// <param name="sqr">the root class sqaure</param>
void RenderWindow::Render(Square* sqr)
{
  if (SDL_RenderCopy(renderer, sqr->GetTexture(), sqr->GetSrcRect(), sqr->GetDstRect()))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture faild to be copied. Error: %s"
      , SDL_GetError());
};

/// <summary>
/// returns the width and the height if the windows
/// becuase its a static program so it is always 1920x1080
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
void RenderWindow::GetWidthHeight(int& w, int& h)
{
  w = 1920;
  h = 1080;
};

/// <summary>
/// retgurns true if the game windows is the current one focused
/// </summary>
/// <returns></returns>
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

/// <summary>
/// returns the renderer struct
/// needed for a few things such as fonts
/// </summary>
/// <returns></returns>
SDL_Renderer* RenderWindow::GetRenderer()
{
  return renderer;
};

/// <summary>
/// displays a solid color rect using the given parameter
/// </summary>
/// <param name="rect">where to display the rect</param>
/// <param name="color">what color to use while displaying</param>
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
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed to render a rect %s", SDL_GetError());
}

/// <summary>
/// copies the flipped texture onto the screen
/// </summary>
/// <param name="tex">the texture to display fipped</param>
/// <param name="src"></param>
/// <param name="dst"></param>
/// <param name="flip">is true then it flips the texture otherwise it just displays it</param>
void RenderWindow::FlipAndPrintTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, bool flip)
{
  SDL_RenderCopyEx(renderer, tex, &src, &dst, 0, NULL, (SDL_RendererFlip)flip);
}
