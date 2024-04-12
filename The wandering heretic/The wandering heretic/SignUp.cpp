#include "SignUp.hpp"
#include <PopUpWindow.hpp>

#define EMAIL_GRAY_TEXT "enter email:"
#define USERNAME_GRAY_TEXT "enter username:"
#define PASSWORD_GRAY_TEXT "enter password;"
#define PASSWORD_CONFIRM_GRAY_TEXT "enter confirm password:"

#define MISSING_DATA "There is one or more missing data"
#define USERNAME_EXIST "USername is already taken"
#define PASSWORD_WEAK "Password is too weak"
#define EMAIL_INVALID "your email is invalid"

//maybe remove startPos
SignUp::SignUp(Vector2i backgroundPos, Vector2i emailStartPos, int margin)
  :_email(nullptr), _username(nullptr), _password(nullptr), _passwordConfirm(nullptr)
  , _background(nullptr), _doneBtn(nullptr),
  _currentTimer(0), _oldTimer(0), _nowDisplay(0)
{
  CreateTextSquares(emailStartPos, margin);
  CreateBackground(backgroundPos, margin);
  CreateDoneButton();
}

SignUp::~SignUp()
{
  delete _email;
  delete _username;
  delete _password;
  delete _passwordConfirm;

  delete _background;
}

bool SignUp::Update()
{
  _background->Update();

  if (!_background->GetTabOpen()) 
    return false;

  SelectFlag();

  _email->Update(_currentSquare == SignUpSquares::email);
  _username->Update(_currentSquare == SignUpSquares::username);
  _password->Update(_currentSquare == SignUpSquares::password);
  _passwordConfirm->Update(_currentSquare == SignUpSquares::passwordConfirm);

  DisplaySquareNames();
  UpdateCursor();
  return UpdatedDoneButton();
}

void SignUp::GetData(std::string* email, std::string* username, std::string* password)
{
  *email = _email->GetWinText()->GetText();
  *username = _username->GetWinText()->GetText();
  *password = _password->GetWinText()->GetText();
}

/// <summary>
/// displays the names of each square 
/// </summary>
void SignUp::DisplaySquareNames()
{
  SDL_Rect* tempRect;
  Vector2i pos;
  constexpr SDL_Color GRAY{ 128, 128, 128, 128 };

  /* email */
  if (_email->GetWinText()->GetText() == "" && _currentSquare != SignUpSquares::email) {
    tempRect = _email->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(EMAIL_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* username */
  if (_username->GetWinText()->GetText() == "" && _currentSquare != SignUpSquares::username) {
    tempRect = _username->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(USERNAME_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* password */
  if (_password->GetWinText()->GetText() == "" && _currentSquare != SignUpSquares::password) {
    tempRect = _password->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(PASSWORD_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* confirm password */
  if (_passwordConfirm->GetWinText()->GetText() == "" && _currentSquare != SignUpSquares::passwordConfirm) {
    tempRect = _passwordConfirm->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(PASSWORD_CONFIRM_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }
}

/// <summary>
/// selects the curremt chosen flags
/// </summary>
void SignUp::SelectFlag()
{
  Mouse* mouse = Mouse::GetMouseInstance();
  Vector2i pos = mouse->GetPos();
  const SDL_Rect posRect{ pos.x, pos.y, 1,1 };

  /* if mouse isnt pressed then dont start selecting */
  if (mouse->GetPressed() != MouseButtons::mbl)
    return;

  /* if a flag isnt chosen then select a square */
  if (SDL_HasIntersection(_email->GetDstRect(), &posRect))
    _currentSquare = SignUpSquares::email;

  else if (SDL_HasIntersection(_username->GetDstRect(), &posRect))
    _currentSquare = SignUpSquares::username;

  else if (SDL_HasIntersection(_password->GetDstRect(), &posRect))
    _currentSquare = SignUpSquares::password;

  else if (SDL_HasIntersection(_passwordConfirm->GetDstRect(), &posRect))
    _currentSquare = SignUpSquares::passwordConfirm;

  else
    _currentSquare = SignUpSquares::none;
}

void SignUp::UpdateCursor()
{
  _currentTimer = SDL_GetTicks();

  Mouse* mouse = Mouse::GetMouseInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Vector2i pos = mouse->GetPos();
  const SDL_Rect posRect{ pos.x, pos.y, 3, 1 };

  if (_currentSquare == SignUpSquares::none)
    return;

  SDL_Rect cursorRect{ 0, 0, 2, LETTER_SIZE };
  cursorRect.y += 1; // so that it wouldnt start from the square outlines
  cursorRect.h -= 2; // so that it wouldnt start from the square outlines

  if (_currentSquare == SignUpSquares::email) {
    SDL_Rect* rect = _email->GetDstRect();
    cursorRect.x += rect->x + _email->GetWinText()->GetTextWidth();
    cursorRect.y += rect->y;
  }

  else if (_currentSquare == SignUpSquares::username) {
    SDL_Rect* rect = _username->GetDstRect();
    cursorRect.x = rect->x + _username->GetWinText()->GetTextWidth();
    cursorRect.y += rect->y;
  }

  else if (_currentSquare == SignUpSquares::password) {
    SDL_Rect* rect = _password->GetDstRect();
    cursorRect.x = rect->x + _password->GetWinText()->GetTextWidth();
    cursorRect.y += rect->y;
  }\
  else if (_currentSquare == SignUpSquares::passwordConfirm) {
    SDL_Rect* rect = _passwordConfirm->GetDstRect();
    cursorRect.x = rect->x + _passwordConfirm->GetWinText()->GetTextWidth();
    cursorRect.y += rect->y;
  }

  if (_nowDisplay)
    window->DisplayRect(&cursorRect, BLACK_COLOR);

  if (_currentTimer - _oldTimer >= CURSOR_COUNTER) {
    _oldTimer = _currentTimer;
    _nowDisplay = !_nowDisplay;
  }
}

bool SignUp::UpdatedDoneButton()
{
  _doneBtn->Update();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->Render((Square*)_doneBtn);

  if (!_doneBtn->GetIsPressed())
    return false;

  std::string email = _email->GetWinText()->GetText();
  std::string username = _username->GetWinText()->GetText();
  std::string password = _password->GetWinText()->GetText();
  std::string passwordConfirm = _passwordConfirm->GetWinText()->GetText();
  if (password != passwordConfirm)
    return false;

  /* check if email user and password are valid */

  return true;
}

/// <summary>
/// Creates the background for the SignUp window
/// </summary>
/// <param name="backgroundPos"></param>
/// <param name="margin"></param>
void SignUp::CreateBackground(Vector2i backgroundPos, int margin)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Xbtn.png");

  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);

  Button* btn = new Button(tex, { 0,0,w,h }, { 0,0,w,h });

  SDL_Rect backgroundRect{ backgroundPos.x, backgroundPos.y, 0, 0 };
  backgroundRect.w = (_email->GetDstRect()->x - backgroundPos.x) * 2 + _email->GetDstRect()->w;
  backgroundRect.h = _email->GetDstRect()->h * 4 + margin * 4;
  
  _background = new PopUpWindow(btn, backgroundRect, BACKGROUND_COLOR, true);
}

/// <summary>
/// Creates the text squares using the startiing
/// position and margin
/// </summary>
/// <param name="emailStartPos"></param>
/// <param name="margin"></param>
void SignUp::CreateTextSquares(Vector2i emailStartPos, int margin)
{
  int SquareHeight = 0;

  _email = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin + SquareHeight;
  SquareHeight = _email->GetDstRect()->h;

  _username = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin + SquareHeight;

  _password = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin + SquareHeight;

  _passwordConfirm = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
}

/// <summary>
/// Creates the done button in the bottom middle background
/// </summary>
void SignUp::CreateDoneButton()
{
  SDL_Rect src{ 0,0,51,51 }, dst{ 0,0,51,51 };

  const char* path = "Assets/GUI/DoneButton.png";
  SDL_Rect backgroundRect = _background->GetRect();
  dst.y = backgroundRect.y + backgroundRect.h - dst.h;
  dst.x = ((backgroundRect.x + backgroundRect.w) / 2) - (dst.w / 2);

  _doneBtn = new Button(path, src, dst);
}

/// <summary>
/// checks if the mail is valid based on the array of domain names
/// </summary>
/// <param name="mail"></param>
/// <returns></returns>
bool SignUp::IsMailValid(std::string& mail)
{
  int startDomainName = mail.find('@');
  std::string domainName = mail.substr(startDomainName, mail.size());

  const char* allDomainNames[] = { "gmail.com", "nomishemer.ort.org" };
  constexpr char DOMMAIN_COUNT = 2;

  for (int i = 0; i < DOMMAIN_COUNT; i++)
    if (!strcmp(domainName.c_str(), "gmail.com"))
      return false;

  return true;
}

/// <summary>
/// returns true if the password is strong
/// </summary>
/// <param name="password"></param>
/// <returns></returns>
bool SignUp::IsPasswordStrong(std::string& password)
{
  if (password.size() < 8)
    return false;

  bool upper = false;
  bool lower = false;
  bool number = false;
  bool special = false;

  for (const char& letter : password) {
    if (letter >= 'A' && letter <= 'Z')
      upper = true;
    else if (letter >= 'a' && letter <= 'z')
      lower = true;
    else if (letter >= '0' && letter <= '9')
      number = true;
    else if (IsLetterSpecial(letter))
      special = true;
  }

  return upper & lower & number & special;
}

/// <summary>
/// returns true if the letter is a special based on the array
/// </summary>
/// <param name="letter"></param>
/// <returns></returns>
bool SignUp::IsLetterSpecial(const char& letter)
{
  const char* allLetters = "~!@#$%^&*()-_+={}[]|/:;<>,?";
  int length = sizeof(allLetters); //its char and char is size of 1

  for (int i = 0; i < length; i++)
    if (allLetters[i] == letter)
      return true;
  return false;
}

#undef EMAIL_GRAY_TEXT 
#undef USERNAME_GRAY_TEXT 
#undef PASSWORD_GRAY_TEXT 
#undef PASSWORD_CONFIRM_GRAY_TEXT

#undef MISSING_DATA 
#undef USERNAME_EXIST
#undef PASSWORD_WEAK 
#undef EMAIL_INVALID 
