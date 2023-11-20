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
  TTF_CloseFont(font);
}

void  WindowText::DisplayText(RenderWindow* window, Vector2i pos, RGBA color) {
  SDL_Color sdlColor;
  sdlColor.a = color.a; sdlColor.r = color.r; sdlColor.b = color.b; sdlColor.g = color.g;
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "put your text here", sdlColor);

  SDL_Rect rect;
  rect.x = pos.x; rect.y = pos.y; rect.w = surfaceMessage->w; rect.h = surfaceMessage->h;

  SDL_Texture* tex = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);

  window->Render(tex, NULL, rect);
}

std::string WindowText:: GetText() {
  return text;
}

void WindowText::SetText(std::string str) {
  text = str;
}

void WindowText::ClearText() {
  text.clear();
}
