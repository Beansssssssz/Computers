#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"
#include "WindowText.hpp"
#include "Utils.hpp"

WindowText::WindowText(const char* fontPath, int size, std::string startingText, int Maxsize)
  :_fontPath(fontPath), text(startingText), _characterSize(size),
  _maxLength(Maxsize), _width(0), _height(0)
{}


/// <summary>
/// displays the text onto the screen, if {-1,-1}
/// is the value of pos then the _pos var will be used instead
/// </summary>
/// <param name="pos">the pos of the text</param>
/// <param name="color">the color of the text</param>
void  WindowText::DisplayText(Vector2i pos, SDL_Color color, bool display) {
  //you cant create a surfarce from no text
  if (text.size() <= 0)
    return;

  if (pos.x == -1 && pos.y == -1)
    pos = _pos;

  TTF_Font* font = TTF_OpenFont(_fontPath, _characterSize);
  if (font == nullptr)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font from path. Error: %s", SDL_GetError());

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);
  if (surfaceMessage == NULL) {
    std::cerr << "Failed to create surface for text rendering: " << TTF_GetError() << std::endl;

    TTF_CloseFont(font);
    return;
  }
  SDL_Texture* message = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);
  if (message == NULL) {
    std::cerr << "Failed to create surface for text rendering: " << TTF_GetError() << std::endl;

    delete surfaceMessage;
    TTF_CloseFont(font);
    return;
  }

  _width = surfaceMessage->w;

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

  Square temp(message, src, dst);
  if(display)
    window->Render(&temp);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);
  TTF_CloseFont(font);
};


/// <summary>
/// changes the character size that the current program is using
/// </summary>
/// <param name="size">the size</param>
void WindowText::SetCharacterSize(int size) {
  _characterSize = size;
}

/// <summary>
/// returns the character size
/// </summary>
/// <returns></returns>
int WindowText::GetCharacterSize()
{
  return _characterSize;
}

/// <summary>
/// sets the value into the _pos value(which is zero by default)
/// from now on this value will display the pos
/// </summary>
/// <param name="pos"></param>
void WindowText::SetPos(Vector2i pos)
{
  _pos = pos;
}

/// <summary>
/// returns the starting pos of the text
/// </summary>
/// <returns></returns>
Vector2i WindowText::GetPos()
{
  return _pos;
}

/// <summary>
/// sets the text to a new text
/// </summary>
/// <param name="str">the text</param>
void WindowText::SetText(std::string str) {
  text = str.substr(0, _maxLength);
  _width = 0;
};

/// <summary>
/// returns the text
/// </summary>
/// <returns>the currently used text</returns>
std::string WindowText:: GetText() {
  return text;
}

/// <summary>
/// clears the text
/// </summary>
void WindowText::ClearText() {
  text.clear();
};

/// <summary>
/// returns the text width
/// </summary>
/// <returns></returns>
int WindowText::GetTextWidth()
{
  if (text.size() <= 0)
    return 0;

  if(_width != 0)
    return _width;

  DisplayText({ -1,-1 }, { 0,0,0,255 }, false);

  return _width;
}

/// <summary>
/// returns the text height which is the same as the character size
/// </summary>
/// <returns></returns>
int WindowText::GetTextHeight()
{
  return _characterSize;
}

/// <summary>
/// returns the maxumin allowed of characters in the text
/// </summary>
/// <returns></returns>
int WindowText::GetMaxCharacters()
{
    return _maxLength;
}

void WindowText::DisplayStaticText(std::string text, Vector2i pos, SDL_Color color, uint8_t letterSize, const char* fontPath)
{

  TTF_Font* font = TTF_OpenFont(fontPath, letterSize);
  if (font == nullptr)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font from path. Error: %s", SDL_GetError());

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);
  if (surfaceMessage == NULL) {
    std::cerr << "Failed to create surface for text rendering: " << TTF_GetError() << std::endl;

    TTF_CloseFont(font);
    return;
  }

  SDL_Texture* message = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);
  if (message == NULL) {
    std::cerr << "Failed to create surface for text rendering: " << TTF_GetError() << std::endl;

    delete surfaceMessage;
    TTF_CloseFont(font);
    return;
  }

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

  Square temp(message, src, dst);
  window->Render(&temp);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);
  TTF_CloseFont(font);
}
