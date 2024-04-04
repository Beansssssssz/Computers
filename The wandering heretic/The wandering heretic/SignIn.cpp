#include "SignIn.hpp"

#include "Keyboard.hpp"

SignIn::SignIn(SDL_Rect backgroundRect, Vector2i emailStartPos, int margin)
  :_backgroundRect(backgroundRect), _email(nullptr), _pass(nullptr)
  , _currentFlag(0)
{
  CreateTextSquares(emailStartPos, margin);
}

SignIn::~SignIn()
{
  delete _email;
  delete _pass;
}


void SignIn::Update()
{
  DisplayBackground();

  SelectFlag();

  _email->Update(_currentFlag == EMAIL_FLAG);
  _pass->Update(_currentFlag == PASSWORD_FLAG);
}

/// <summary>
/// find out which flag is supposed to be on
/// </summary>
void SignIn::SelectFlag()
{
  Mouse* mouse = Mouse::GetMouseInstance();
  Vector2i pos = mouse->GetPos();
  const SDL_Rect posRect{ pos.x, pos.y, 1,1 };

  /* if mouse isnt pressed then dont start selecting */
  if (mouse->GetPressed() != MouseButtons::mbl)
    return;

  /* if a flag isnt chosen then select a square */
  if (SDL_HasIntersection(_email->GetDstRect(), &posRect))
    _currentFlag = EMAIL_FLAG;

  else if (SDL_HasIntersection(_pass->GetDstRect(), &posRect))
    _currentFlag = PASSWORD_FLAG;

  else
    _currentFlag = 0;
}

/// <summary>
/// displays the background rect.
/// </summary>
void SignIn::DisplayBackground()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  window->DisplayRect(&_backgroundRect, BACKGROUND_COLOR);
}

/// <summary>
/// creates the Squares where the user writes text in
/// </summary>
/// <param name="emailStartPos"></param>
/// <param name="margin"></param>
void SignIn::CreateTextSquares(Vector2i& emailStartPos, int& margin)
{
  _email = new TextSquare(emailStartPos, 1, LETTER_SIZE, 30);
  emailStartPos.y += margin;
  _pass = new TextSquare(emailStartPos, 1, LETTER_SIZE, 30);
}


