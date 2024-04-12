#include "SignIn.hpp"

#include "Keyboard.hpp"

#define EMAIL_GRAY_TEXT "Enter email or username here"
#define PASSWORD_GRAY_TEXT "Enter your password here"

SignIn::SignIn(Vector2i backgroundPos, Vector2i emailStartPos, int margin)
  :_background(nullptr), _email(nullptr), _pass(nullptr), _doneBtn(nullptr)
  , _currentSquare(Squares::none), _currentTimer(0),
  _nowDisplay(false), _oldTimer(0)
{
  CreateTextSquares(emailStartPos, margin);
  CreateBackground(backgroundPos, margin);
  CreateDoneButton();
}

SignIn::~SignIn()
{
  delete _email;
  delete _pass;
}

/// <summary>
/// the SignIn main function, updates everything inside the fucntion and
/// true if the done button was pressed and if the password and email where valid
/// </summary>
/// <returns></returns>
bool SignIn::Update()
{
  _background->Update();
  if (!_background->GetTabOpen())
    return false;

  SelectFlag();

  _email->Update(_currentSquare == Squares::email);
  _pass->Update(_currentSquare == Squares::password);

  DisplaySquareNames();
  UpdateCursor();
  return UpdatedDoneButton();
}

/// <summary>
/// retuns the data using out paramaters
/// </summary>
/// <param name="email">OUT the passsword the user inputed</param>
/// <param name="password">OUT the email or usernames the user inputed</param>
void SignIn::GetData(std::string* email, std::string* password)
{
  *email = _email->GetWinText()->GetText();
  *password = _pass->GetWinText()->GetText();
}

/// <summary>
/// dispalyes the names of the squares and what to do in each one
/// </summary>
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
  _currentTimer = SDL_GetTicks();

  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Vector2i pos = mouse->GetPos();
  const SDL_Rect posRect{ pos.x, pos.y, 3, 1 };

  if (_currentSquare == Squares::none)
    return;

  SDL_Rect cursorRect{ 0, 0, 2, LETTER_SIZE };
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

  if (_nowDisplay)
    window->DisplayRect(&cursorRect, BLACK_COLOR);

  if (_currentTimer - _oldTimer >= CURSOR_COUNTER) {
    _oldTimer = _currentTimer;
    _nowDisplay = !_nowDisplay;
  }
}

/// <summary>
/// updates and displays the done button and check if it was pressed
/// if yes then check whether or not the email/username
/// with the password where valid
/// </summary>
    /// <returns></returns>
bool SignIn::UpdatedDoneButton()
{
  _doneBtn->Update();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->Render((Square*)_doneBtn);

  if (!_doneBtn->GetIsPressed())
    return false;

  std::string email = _email->GetWinText()->GetText();
  std::string pass = _pass->GetWinText()->GetText();
  /* check if email and password are valid */

  return true;
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

/// <summary>
/// creates the background
/// </summary>
/// <param name="backgroundPos"></param>
/// <param name="margin"></param>
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

/// <summary>
/// creates the done button at the bottom middle of the screen
/// </summary>
void SignIn::CreateDoneButton()
{
  SDL_Rect src{ 0,0,51,51 }, dst{ 0,0,51,51 };

  const char* path = "Assets/GUI/DoneButton.png";
  SDL_Rect backgroundRect = _background->GetRect();
  dst.y = backgroundRect.y + backgroundRect.h - dst.h;
  dst.x = ((backgroundRect.x + backgroundRect.w) / 2) - (dst.w / 2);

  _doneBtn = new Button(path, src, dst);
}
