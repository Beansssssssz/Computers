#include "SignIn.hpp"

#include "Keyboard.hpp"

SignIn::SignIn(Vector2i backgroundPos, Vector2i emailStartPos, int margin)
  :_background(nullptr), _email(nullptr), _pass(nullptr)
  , _currentSquare(Squares::none), currentTimer(0),
  _nowDisplay(false), _oldTimer(0)
{
  CreateTextSquares(emailStartPos, margin);
  CreateBackground(backgroundPos, margin);
}

SignIn::~SignIn()
{
  delete _email;
  delete _pass;
}


void SignIn::Update()
{
  _background->Update();
  if (!_background->GetTabOpen())
    return;

  SelectFlag();

  _email->Update(_currentSquare == Squares::email);
  _pass->Update(_currentSquare == Squares::password);

  DisplaySquareNames();
  UpdateCursor();
}

void SignIn::DisplaySquareNames()
{
  SDL_Rect* tempRect;
  Vector2i pos;
  constexpr SDL_Color GRAY{ 128, 128, 128, 128 };

  /* email */
  if (_email->GetWinText()->GetText() == "" && _currentSquare != Squares::email) {
    tempRect = _email->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(EMAIL_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* password */
  if (_pass->GetWinText()->GetText() == "" && _currentSquare != Squares::password) {
    tempRect = _pass->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(PASSWORD_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }
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

  if (SDL_HasIntersection(_email->GetDstRect(), &posRect))
    _currentSquare = Squares::email;

  else if (SDL_HasIntersection(_pass->GetDstRect(), &posRect))
    _currentSquare = Squares::password;

  else
    _currentSquare = Squares::none;
}

/// <summary>
/// updtes the flashing cursor
/// </summary>
void SignIn::UpdateCursor()
{
  currentTimer = SDL_GetTicks();

  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Vector2i pos = mouse->GetPos();
  const SDL_Rect posRect{ pos.x, pos.y, 3, 1 };

  if (_currentSquare == Squares::none)
    return;

  SDL_Rect cursorRect{ 0, 0, 2, LETTER_SIZE};
  cursorRect.y += 1; // so that it wouldnt start from the square outlines
  cursorRect.h -= 2; // so that it wouldnt start from the square outlines

  if (_currentSquare == Squares::email) {
    SDL_Rect* rect = _email->GetDstRect();
    cursorRect.x += rect->x + _email->GetWinText()->GetTextWidth();
    cursorRect.y += rect->y;
  }

  else if (_currentSquare == Squares::password) {
    SDL_Rect* rect = _pass->GetDstRect();
    cursorRect.x = rect->x + _pass->GetWinText()->GetTextWidth();
    cursorRect.y += rect->y;
  }

  if(_nowDisplay)
    window->DisplayRect(&cursorRect, BLACK_COLOR);

  if (currentTimer - _oldTimer >= CURSOR_COUNTER) {
    _oldTimer = currentTimer;
    _nowDisplay = !_nowDisplay;
  }
}

/// <summary>
/// creates the Squares where the user writes text in
/// </summary>
/// <param name="emailStartPos"></param>
/// <param name="margin"></param>
void SignIn::CreateTextSquares(Vector2i& emailStartPos, int& margin)
{
  _email = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin;
  _pass = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
}

void SignIn::CreateBackground(Vector2i backgroundPos, int margin)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Xbtn.png");

  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);

  Button* btn = new Button(tex, { 0,0,w,h }, { 0,0,w,h });

  SDL_Rect backgroundRect{ backgroundPos.x, backgroundPos.y, 0, 0 };
  backgroundRect.w = (_email->GetDstRect()->x - backgroundPos.x) * 2 + _email->GetDstRect()->w;
  backgroundRect.h = _email->GetDstRect()->h * 2 + margin * 2;

  _background = new PopUpWindow(btn, backgroundRect, BACKGROUND_COLOR, true);
}

#undef EMAIL_GRAY_TEXT 
#undef PASSWORD_GRAY_TEXT 
