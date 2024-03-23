#include "TextSquare.hpp"

#include "RenderWindow.hpp"
#include "Keyboard.hpp"
#include "WindowText.hpp"

TextSquare::TextSquare(SDL_Rect dst, uint8_t outlineSize, uint8_t characterSize, uint8_t maxLength, bool stopBuildText)
  :_dst(dst), _outlineSize(outlineSize), _winText(nullptr), _stopBuildText(stopBuildText)
{
  const char* fontPath = "Assets/Fonts/font.otf";
  _winText = new WindowText(fontPath, characterSize, "", maxLength);

  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  keyboard->StartBuildText();
  keyboard->SetText("");
}

TextSquare::~TextSquare() {
  delete _winText;

  if (_stopBuildText)
  {
    Keyboard* keyboard = Keyboard::GetKeyboardInstance();
    keyboard->StopBuildText();
  }
}


void TextSquare::Update()
{
  /* print out the rect and its outline */
  DisplaySquare();

  /* check for input */
  InputText();

  /* print out the current buffer */
  _winText->DisplayText({ _dst.x, _dst.y });
}

/// <summary>
/// displays the rect with its outline into the screen
/// </summary>
void TextSquare::DisplaySquare()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  _outlineSize = 1;
  /* creating the outline rect */
  SDL_Rect outlineRect = _dst;
  outlineRect.x -= _outlineSize;
  outlineRect.y -= _outlineSize;
  outlineRect.w += _outlineSize * 2;
  outlineRect.h += _outlineSize * 2;

  /* displays the rects onto the screen */
  window->DisplayRect(&outlineRect, BLACK);
  window->DisplayRect(&_dst, WHITE);
}

/// <summary>
/// get the current inputed text and delets everything after the current max limit
/// of characters
/// </summary>
void TextSquare::InputText()
{
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  std::string currentText = keyboard->GetText();

  int maxLength = _winText->GetMaxCharacters();
  currentText = currentText.substr(0, maxLength);

  keyboard->SetText(currentText);
  _winText->SetText(currentText);
}
