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


  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ch, sdlColor);

  if (surfaceMessage == NULL)
    std::cout << "Text failed to render. Error: " << TTF_GetError() << std::endl;

  SDL_Rect rect;
  rect.x = pos.x; rect.y = pos.y; rect.w = surfaceMessage->w; rect.h = surfaceMessage->h;

  CreateSquare(window, rect, RGBA(255, 255, 255, 255));

  SDL_Texture* tex = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);

  window->Render(tex, NULL, rect);
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
