#include "ChooseNumber.hpp"

ChooseNumber::ChooseNumber(char buttons_number)
  :_btns(nullptr), _tab(nullptr),
  _len(buttons_number)
{
  CreateWindow();
  CreateButtons();
  CreateWindowText();
}

ChooseNumber::~ChooseNumber()
{
  delete[] _btns;
  delete _tab;
  delete _text;
}

/// <summary>
/// returns a number between 1 - 128 if the user chose a button.
/// if no number was chossen then returns 0.
/// if the window was closed then returns a -1;
/// </summary>
char ChooseNumber::Update()
{
  if (!UpdateWindow())
    return -1;

  return UpdateButtons();
}

/// <summary>
/// returns true if the tab is currently open
/// </summary>
/// <returns></returns>
bool ChooseNumber::GetIsOpen() {
  return this->_tab->GetTabOpen();
}

/// <summary>
/// Sets the tab
/// if it's closed or open
/// </summary>
/// <returns></returns>
void ChooseNumber::SetOpen(bool state) {
  this->_tab->SetTabOpen(false);
}

/// <summary>
/// updates the window and checks if the window was closed
/// if window was closed then returns false
/// otherwise returns true.
/// </summary>
/// <returns></returns>
bool ChooseNumber::UpdateWindow()
{
  _tab->Update();

  return _tab->GetTabOpen();
}

/// <summary>
/// updates the buttons and checks if any buttons was pressed,
/// if yes the returns the last button pressed.
/// if a buttons was pressed then it returns the pressed numbers number
/// otherwise returns 0;
/// </summary>
/// <returns></returns>
char ChooseNumber::UpdateButtons()
{
  int ret = 0;

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  for (char i = 0; i < _len; i++) {
    if (_btns[i]->GetIsReleased())
      ret = i + 1;

    window->Render(_btns[i]);
    _btns[i]->Update();
  }

  WriteOnButtons();
  return ret;
}

/// <summary>
/// Displays the Text on the button
/// </summary>
void ChooseNumber::WriteOnButtons()
{
  for (int i = 1; i < _len + 1; i++)
  {
    _text->SetText(std::to_string(i));

    int size = _text->GetCharacterSize();
    SDL_Rect rect = *_btns[i - 1]->GetDstRect();
    Vector2i pos{ rect.x, rect.y };

    pos.x += rect.w / 2 - size / 2;
    pos.y += rect.h / 2 - size / 2;
    _text->SetPos(pos);

    _text->DisplayText();
  }
}

void ChooseNumber::CreateButtons()
{
  _btns = new Button * [_len];

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/ButtonOutline.png");

  int imageW, imageH;
  SDL_QueryTexture(tex, NULL, NULL, &imageW, &imageH);
  
  SDL_Rect tabRect = _tab->GetRect();

  /* finding the margins between each button */

  //X:
  int totalWidth = imageW * MAX_PER_ROW;
  int TotalMargin = tabRect.w - totalWidth;

  int marginX = TotalMargin / (MAX_PER_ROW);

  //Y:
  int totalRows = (_len / MAX_PER_ROW);
  if (_len % MAX_PER_ROW != 0)
    totalRows++;

  int totalHeight = imageH * totalRows;
  TotalMargin = tabRect.h - totalHeight;

  int marginY = TotalMargin / (totalRows + 1);

  /* create the Rects for all the button */
  SDL_Rect dst{ marginX + tabRect.x, marginY + tabRect.y, imageW, imageH },
    src{ 0, 0, imageW, imageH };

  /* starts createing the buttons */
  char counter = 0;
  for (char i = 0; i < _len; i++)
  {
    if (counter >= MAX_PER_ROW)
    {
      dst.y += marginY;
      dst.x = marginX + tabRect.x;
      counter = 0;
    }
    _btns[i] = new Button(tex, src, dst);

    dst.x += marginX;
    counter++;
  }
}

void ChooseNumber::CreateWindow()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Xbtn.png");
  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);
  Button* btn = new Button(tex, { 0,0,w,h }, { 0,0,w,h });

  SDL_Rect rect;
  RenderWindow::GetWidthHeight(w, h);

  rect.x = (int)(w * (1.0f / 6.0f));
  rect.y = (int)(h * (1.0f / 6.0f));
  rect.w = (int)(w * (4.0f / 6.0f));
  rect.h = (int)(h * (4.0f / 6.0f));

  SDL_Color _color{ 255,100,100,255 };

  _tab = new PopUpWindow(btn, rect, _color, true);
}

void ChooseNumber::CreateWindowText()
{
  _text = new WindowText();

  //i used a log formula to get the amount of digits in _len
  int size = (int)(_btns[0]->GetDstRect()->w / (log10((double)_len) + 1));
  _text->SetCharacterSize(size + 5);//the 5 is a magic number(aka adjustments)
}
