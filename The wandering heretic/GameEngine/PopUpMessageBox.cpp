#include "PopUpMessageBox.hpp"


PopUpMessageBox::PopUpMessageBox(Button* btnExit, SDL_Rect tab, SDL_Color color, std::string text, bool open)
  :PopUpWindow(btnExit, tab, color, open),
  _text(text), _winText(nullptr)
{
  CreateWindowText();
}

PopUpMessageBox::~PopUpMessageBox()
{}

void PopUpMessageBox::Update()
{
  PopUpWindow::Update();

  if (!_tabOpen)
    return;

  _winText->DisplayText();
}

/// <summary>
/// creates the windows text and updates the old data
/// </summary>
void PopUpMessageBox::CreateWindowText()
{
  _winText = new WindowText();
  _winText->SetText(_text);

  int width = _winText->GetTextWidth();
  int height = _winText->GetTextHeight();

  SDL_Rect newTabRect = this->GetRect();
  newTabRect.w = width;
  newTabRect.h = height;
  this->SetTabRect(newTabRect);

  Vector2i pos{ newTabRect.x, newTabRect.y };
  _winText->SetPos(pos);
}
