#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "WindowText.hpp"
#include "Utils.hpp"


WindowText::WindowText(const char* fontPath, int size, std::string str, int Maxsize)
  :text(str), lengthMaxSize(Maxsize), characterSize(size)
{
  font = TTF_OpenFont(fontPath, characterSize);
}

WindowText:: ~WindowText() {
}

void  WindowText::DisplayText(RenderWindow* window, Vector2i pos, RGBA color) {
  //you cant create a surfarce from no text
  if (text.size() <= 0)
    return;
  const char* ch = text.c_str();

  SDL_Color sdlColor = utils::ChangeRgbaToSdlColor(color);

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, ch, sdlColor);
  SDL_Texture* message = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = surfaceMessage->w;
  src.h = surfaceMessage->h;

  SDL_Rect dst;
  dst.x = pos.x;
  dst.y = pos.y;
  dst.w = src.w;
  dst.h = src.h;

  Square sqr(message, src, dst);
  window->Render(sqr);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);
}

void WindowText::CreateSquare(RenderWindow* window, SDL_Rect rect, RGBA color)
{
  rect.w = 9 * characterSize;
  window->CreateRect(&rect, color);
};

std::string WindowText:: GetText() {
  return text;
}

void WindowText::SetText(std::string str) {
  if (str.size() > lengthMaxSize)
    return;
  text = str;
};

void WindowText::ClearText() {
  text.clear();
};
