#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Keyboard.hpp"

Keyboard::Keyboard()
  :_keysArray(NULL), _input(false), _keyPressed(false)
  ,_keyDeleted(false)
{};

Keyboard* Keyboard::GetKeyboardInstance()
{
	if (_keyboardPtr == NULL)
	{
    _keyboardPtr = new Keyboard();
		return _keyboardPtr;
	}
	else
		return _keyboardPtr;
}

Keyboard::~Keyboard()
{
  StopBuildText();
};

Uint8* Keyboard::GetKeyArray()
{
  return _keysArray;
}

std::string Keyboard::GetText()
{
  return text;
}

void Keyboard::SetText(std::string str)
{
  text = str;
}

void Keyboard::EmptyText()
{
  text.clear();
};

void Keyboard::StopBuildText(bool clear)
{
  SDL_StopTextInput();
  if (clear)
    text.clear();
  _input = false;
};

void Keyboard::StartBuildText()
{
  SDL_StartTextInput();
  _input = true;
};

void Keyboard::BuildText(SDL_Event event)
{
  if (!_input)
    return;

  if (event.type == SDL_KEYDOWN)
  {

    std::cout << "aa\n";
  }

  if (event.type == SDL_TEXTINPUT && text.size() < LIMIT)
    text += event.text.text;

  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE) {
    _keyDeleted = true; 
    if (!text.empty())
      text.pop_back();
  }
  else if (event.type == SDL_KEYDOWN)
    _keyDeleted = false;

  // removes the first element if its space
  if(text.c_str()[0] == ' ')
    text.erase(text.begin());
};

void Keyboard::Update()
{
  _keyPressed = false;
  SDL_PumpEvents();

  _keysArray = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
  for (int i = 0; i < 250; i++)//all the keys on the keyboard
    if (_keysArray[i])
      _keyPressed = true;
};

/// <summary>
/// return true of any key press is happing
/// otherwise returns false
/// </summary>
bool Keyboard::IsKeyPressed()
{
  return _keyPressed;
}

/// <summary>
/// returns true if the last action was deleteing a letter
/// otherwise returns true
/// </summary>
/// <returns></returns>
bool& Keyboard::DeletedLetter()
{
  return _keyDeleted;
};
