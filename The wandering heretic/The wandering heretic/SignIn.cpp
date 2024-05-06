#include "SignIn.hpp"

#include "Keyboard.hpp"
#include "Server.hpp"

#define EMAIL_GRAY_TEXT "Enter email or username here"
#define PASSWORD_GRAY_TEXT "Enter your password here"

#define MISSING_FIELDS "one or more fields is missing."
#define INCORRECT_DATA "password or login is incorrect."

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
  DisplaySquareTitles();
  UpdateCursor();
  DisplayErrorMessage();

  return UpdatedDoneButton();
}

/// <summary>
/// retuns the data inputed into signIn by the user
/// </summary>
/// <returns></returns>
UserData SignIn::GetData()
{
  UserData data{ "", "", _pass->GetWinText()->GetText(), nullptr};

  std::string email = _email->GetWinText()->GetText();

  if (email.find('@') == std::string::npos)
    data.username = email;
  else
    data.email = email;

  return data;
}

/// <summary>
/// return true if the background of the SignIn is closed
/// </summary>
/// <returns></returns>
bool SignIn::IsOpen()
{
	return _background->GetTabOpen();
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
    WindowText::DisplayStaticText(EMAIL_GRAY_TEXT, { tempRect->x , tempRect->y }, GRAY, LETTER_SIZE);
  }

  /* password */
  if (_pass->GetWinText()->GetText() == "" && _currentSquare != Squares::password) {
    tempRect = _pass->GetDstRect();
    WindowText::DisplayStaticText(PASSWORD_GRAY_TEXT, { tempRect->x , tempRect->y }, GRAY, LETTER_SIZE);
  }
}

/// <summary>
/// displays each of the sqaures titles
/// </summary>
void SignIn::DisplaySquareTitles()
{
  SDL_Rect tempRect;
  Vector2i pos;
  constexpr SDL_Color WHITE{ 255, 255, 255, 255 };
  std::string currentText;

  /* email */
  currentText = "Login:";
  tempRect = *_email->GetDstRect();
  tempRect.y -= TITLE_LETTER_SIZE;
  WindowText::DisplayStaticText(currentText, { tempRect.x , tempRect.y }, WHITE, TITLE_LETTER_SIZE);


  /* password */
  currentText = "Password:";
  tempRect = *_pass->GetDstRect();
  tempRect.y -= TITLE_LETTER_SIZE;
  WindowText::DisplayStaticText(currentText, {tempRect.x , tempRect.y}, WHITE, TITLE_LETTER_SIZE);
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
/// displays the current error message
/// </summary>
void SignIn::DisplayErrorMessage()
{
  /* check */
  Vector2i pos{ 0,0 };
  pos.y = _doneBtn->GetDstRect()->y;//the 2 is there for spacing
  pos.x = _background->GetRect().x + 2;

  WindowText::DisplayStaticText(_errorMsg, pos, ERROR_LETTER_COLOR, ERROR_LETTER_SIZE);
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


  /* check if all fields are full */
  if (_pass->GetWinText()->GetText().empty() || _email->GetWinText()->GetText().empty()) {
    _errorMsg = MISSING_FIELDS;
    return false;
  }

  if(this->CheckIfDataIsValid())
    return true;

  /* display bad message */
  _errorMsg = INCORRECT_DATA;
  return false;
}

/// <summary>
/// checks whether not a email or a username was inputed
/// afterwise returns true if the user exists in the database
/// </summary>
/// <returns></returns>
bool SignIn::CheckIfDataIsValid()
{
  Server* server = Server::GetServerInstance();
  std::string email = _email->GetWinText()->GetText();
  std::string pass = _pass->GetWinText()->GetText();
  UserData data{ "", "", pass, nullptr };
  /* check if the inputed field was username or email */
  //if there is a @ then the username is invalid thus its an email
  size_t domainStartLoc = email.find('@');
  if (domainStartLoc != -1)
    data.email = email;
  else
    data.username = email;

  return server->DoesUserExist(data);
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
  backgroundRect.h = _email->GetDstRect()->h * 2 + margin * 2 + (int)(ERROR_LETTER_SIZE * 1.5);

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
  dst.x = backgroundRect.x + backgroundRect.w / 2 - dst.w / 2;

  _doneBtn = new Button(path, src, dst);
}

#undef EMAIL_GRAY_TEXT
#undef PASSWORD_GRAY_TEXT

#undef MISSING_FIELDS
#undef INCORRECT_DATA
