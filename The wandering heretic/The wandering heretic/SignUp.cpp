#include "SignUp.hpp"
#include <PopUpWindow.hpp>

#define EMAIL_GRAY_TEXT "email"
#define USERNAME_GRAY_TEXT "username"
#define PASSWORD_GRAY_TEXT "password"
#define PASSWORD_CONFIRM_GRAY_TEXT "confirm password"

//maybe remove startPos
SignUp::SignUp(Vector2i backgroundPos, Vector2i emailStartPos, int margin)
  :_email(nullptr), _username(nullptr), _password(nullptr), _passwordConfirm(nullptr)
  , _background(nullptr)
{
  CreateTextSquares(emailStartPos, margin);
  CreateBackground(backgroundPos, margin);
}

SignUp::~SignUp()
{
  delete _email;
  delete _username;
  delete _password;
  delete _passwordConfirm;

  delete _background;
}

void SignUp::Update()
{
  _background->Update();

  if (!_background->GetTabOpen())
    return;

  SelectFlag();

  _email->Update(_currentFlag == EMAIL_FLAG);
  _username->Update(_currentFlag == USERNAME_FLAG);
  _password->Update(_currentFlag == PASSWORD_FLAG);
  _passwordConfirm->Update(_currentFlag == PASSWORD_CONFIRM_FLAG);

  DisplaySquareNames();
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
  if (_email->GetWinText()->GetText() == "" && _currentFlag == EMAIL_FLAG) {
    tempRect = _email->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(EMAIL_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* username */
  if (_username->GetWinText()->GetText() == "" && _currentFlag == USERNAME_FLAG) {
    tempRect = _username->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(USERNAME_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* password */
  if (_password->GetWinText()->GetText() == "" && _currentFlag == PASSWORD_FLAG) {
    tempRect = _password->GetDstRect();
    pos.x = tempRect->x;
    pos.y = tempRect->y;
    WindowText::DisplayStaticText(PASSWORD_GRAY_TEXT, pos, GRAY, LETTER_SIZE);
  }

  /* confirm password */
  if (_passwordConfirm->GetWinText()->GetText() == "" && _currentFlag == PASSWORD_CONFIRM_FLAG) {
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
    _currentFlag = EMAIL_FLAG;

  else if (SDL_HasIntersection(_username->GetDstRect(), &posRect))
    _currentFlag = EMAIL_FLAG;

  else if (SDL_HasIntersection(_password->GetDstRect(), &posRect))
    _currentFlag = EMAIL_FLAG;

  else if (SDL_HasIntersection(_passwordConfirm->GetDstRect(), &posRect))
    _currentFlag = EMAIL_FLAG;

  else
    _currentFlag = 0;
}

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
