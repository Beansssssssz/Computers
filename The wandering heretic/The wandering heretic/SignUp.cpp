#include "SignUp.hpp"

SignUp::~SignUp()
{
  delete _email;
  delete _username;
  delete _password;
  delete _passwordConfirm;
}

void SignUp::CreateTextSquares()
{

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

  for (const char& letter : pass) {
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
