#include "SignUp.hpp"
#include <PopUpWindow.hpp>

SignUp::SignUp(SDL_Rect backgroundRect, Vector2i emailStartPos, int margin)
  :_email(nullptr), _username(nullptr), _password(nullptr), _passwordConfirm(nullptr)
  , _background(nullptr)
{
  CreateTextSquares(emailStartPos, margin);
  CreateBackground(backgroundRect);
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

  SelectFlag();

  _email->Update(_currentFlag == EMAIL_FLAG);
  _username->Update(_currentFlag == USERNAME_FLAG);
  _password->Update(_currentFlag == PASSWORD_FLAG);
  _passwordConfirm->Update(_currentFlag == PASSWORD_CONFIRM_FLAG);
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

  if (SDL_HasIntersection(_password->GetDstRect(), &posRect))
    _currentFlag = EMAIL_FLAG;

  else if (SDL_HasIntersection(_passwordConfirm->GetDstRect(), &posRect))
    _currentFlag = EMAIL_FLAG;

  else
    _currentFlag = 0;
}

void SignUp::CreateBackground(SDL_Rect backgroundRect)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Xbtn.png");

  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);

  Button* btn = new Button(tex, { 0,0,w,h }, { 0,0,w,h });
  _background = new PopUpWindow(btn, backgroundRect, BACKGROUND_COLOR, true);
}

void SignUp::CreateTextSquares(Vector2i emailStartPos, int margin)
{
  _email = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin;

  _username = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin;

  _password = new TextSquare(emailStartPos, 1, LETTER_SIZE, MAX_LETTERS);
  emailStartPos.y += margin;

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
