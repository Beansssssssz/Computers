#include "InputText.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

InputText::InputText(std::string example, Vector2i pos)
  :_exampleText(example), _pos(pos), timer(timer = SDL_GetTicks()),
  counter(0), _winText(new WindowText())
  ,WIDTH(LIMIT * _winText->GetCharacterSize() / 3 + 5)//i change the size by 3 times less(5 is padding)
  ,HEIGHT(_winText->GetCharacterSize()/ 3 + 5)//i change the size by 3 times less(5 is pading)
{
  _winText->SetCharacterSize(10);

  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  keyboard->StartBuildText();
  keyboard->EmptyText();
}

InputText::~InputText()
{
  delete _winText;
  Mouse* mouse = Mouse::GetMouseInstance();
  mouse->ShowMouse(true);
}

void InputText::Update(bool input)
{
  Mouse* mouse = Mouse::GetMouseInstance();
  mouse->ShowMouse(false);

  DisplayRect();
  DisplayText(input);
  if(input)
    DisplayFlashingCursor();
}

std::string InputText::GetText()
{
  return _text;
}

const int InputText::GetSquareWidth()
{
  return WIDTH;
}

const int InputText::GetSquareHeight()
{
  return HEIGHT;
}

SDL_Rect InputText::GetRect()
{
  return SDL_Rect{_pos.x, _pos.y, WIDTH, HEIGHT};
}

/// <summary>
/// displays the rect and an outline onto the screen
/// </summary>
void InputText::DisplayRect()
{
  const SDL_Color WHITE{ 255,255,255,255 };
  const SDL_Color GRAY{ 128,128,128,255 };
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //create outline
  SDL_Rect rect{ _pos.x - 1, _pos.y - 1, WIDTH + 2, HEIGHT + 2 };//for the outlines
  window->DisplayRect(&rect, GRAY);

  //create inside
  rect.x++; rect.y++;
  rect.w -= 2; rect.h -= 2;
  window->DisplayRect(&rect, WHITE);
}

/// <summary>
/// Displays the text onto the screen
/// </summary>
void InputText::DisplayText(bool input)
{
  const SDL_Color BLACK{ 0,0,0,255 };
  const SDL_Color GRAY{ 128,128,128,255 };

  Keyboard* keyboard = Keyboard::GetKeyboardInstance();

  _text = keyboard->GetText();
  if (!input)
    return;

  if (_text.size() <= 0) {
    _winText->SetText(_exampleText);
    _winText->DisplayText(_pos, GRAY);
  }
  else {
    _winText->SetText(_text);
    _winText->DisplayText(_pos, BLACK);
  }
};

/// <summary>
/// displays the a flashing cursor onto the postion of the last character
/// </summary>
void InputText::DisplayFlashingCursor()
{
  if (_text.size() <= 0)
    return;

  counter = SDL_GetTicks();
  if (timer + 500 > counter)
    return;
  if (counter > timer + 1000)
    timer = counter;

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  const SDL_Color BLACK{0, 0, 0, 255};

  int x = _pos.x + _winText->GetTextWidth(),
    h = _winText->GetTextHeight();

  SDL_Rect rect{ x, _pos.y, 1, h };
  window->DisplayRect(&rect, BLACK);
};
