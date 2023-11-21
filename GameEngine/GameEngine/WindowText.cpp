#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "WindowText.hpp"
#include "Math.hpp"


WindowText::WindowText(const char* fontPath, int size, std::string str) {
  font = TTF_OpenFont(fontPath, size);
  text = str;
}

WindowText:: ~WindowText() {
}

void  WindowText::DisplayText(RenderWindow* window, Vector2i pos, RGBA color) {
  //you cant create a surfarce from no text
  if (text.size() <= 0)
    return;
  const char* ch = text.c_str();

  SDL_Color sdlColor;
  sdlColor.a = color.a; sdlColor.r = color.r; sdlColor.b = color.b; sdlColor.g = color.g;

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ch, sdlColor);

  if (surfaceMessage == NULL)
    std::cout << "Text failed to render. Error: " << TTF_GetError() << std::endl;

  SDL_Rect rect;
  rect.x = pos.x; rect.y = pos.y; rect.w = surfaceMessage->w; rect.h = surfaceMessage->h;

  SDL_Texture* tex = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);

  window->Render(tex, NULL, rect);
}

std::string WindowText:: GetText() {
  return text;
}

void WindowText::SetText(std::string str) {
  if (str.size() > 30)
    return;
  text = str;
  return;
}

void WindowText::ClearText() {
  text.clear();
}
