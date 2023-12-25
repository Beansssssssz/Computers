#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderWindow.hpp"
#include "WindowText.hpp"
#include "Utils.hpp"

WindowText::WindowText(const char* fontPath, int size, std::string str, int Maxsize)
  :_fontPath(fontPath), text(str), _characterSize(size), _maxLength(Maxsize)
{
  font = TTF_OpenFont(_fontPath, _characterSize);

  _width = 0;
};

WindowText::~WindowText()
{
  TTF_CloseFont(font);
};

/// <summary>
/// displays the text onto the screen, if {-1,-1}
/// is the value of pos then the _pos var will be used instead
/// </summary>
/// <param name="pos">the pos of the text</param>
/// <param name="color">the color of the text</param>
void  WindowText::DisplayText(Vector2i pos, SDL_Color color) {
  //you cant create a surfarce from no text
  if (text.size() <= 0)
    return;

  if (pos.x == -1 && pos.y == -1)
    pos = _pos;

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* message = SDL_CreateTextureFromSurface(window->GetRenderer(), surfaceMessage);

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
  window->Render(&temp);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);
};

/// <summary>
/// update
/// </summary>
/// <param name="rect"></param>
/// <param name="color"></param>
void WindowText::CreateSquare(SDL_Rect rect, SDL_Color color)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  rect.w = 9 * _characterSize;
  window->DisplayRect(&rect, color);
};

/// <summary>
/// remakes the font
/// </summary>
void WindowText::RemakeFont()
{
  TTF_CloseFont(font);
  font = TTF_OpenFont(_fontPath, _characterSize);
};

/// <summary>
/// changes the character size that the current program is using
/// </summary>
/// <param name="size">the size</param>
void WindowText::SetCharacterSize(int size) {
  _characterSize = size;
  RemakeFont();
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
/// sets the text to a new text
/// </summary>
/// <param name="str">the text</param>
void WindowText::SetText(std::string str) {
  if (str.size() > _maxLength)
    return;
  text = str;
};

/// <summary>
/// returns the text
/// </summary>
/// <returns>the currently used text</returns>
std::string WindowText:: GetText() {
  return text;
}

/// <summary>
/// returns the text width
/// </summary>
/// <returns></returns>
int WindowText::GetTextWidth()
{
  if(!(_width <= 0 && text.size() > 0))
    return _width;

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(),
    { 0,0,0,0 });
  SDL_Texture* message = SDL_CreateTextureFromSurface(window->GetRenderer(),
    surfaceMessage);

  _width = surfaceMessage->w;

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);

  return _width;
}

Vector2i WindowText::GetPos()
{
  return _pos;
}

/// <summary>
/// clears the text
/// </summary>
void WindowText::ClearText() {
  text.clear();
};
