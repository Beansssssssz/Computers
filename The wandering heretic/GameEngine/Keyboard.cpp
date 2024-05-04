#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Keyboard.hpp"

Keyboard::Keyboard()
  :_keysArray(nullptr), _input(false), _keyPressed(false)
{};

/// <summary>
/// returns the instance to the static object of this class
/// this is the only way to get an object of this class
/// this always returns the same object
/// </summary>
/// <returns></returns>
Keyboard* Keyboard::GetKeyboardInstance()
{
	if (_keyboardPtr == nullptr)
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

/// <summary>
/// returns the key array
/// the key array is built using SDL and checks for key pressed
/// in order to check u need to use the scan codes provided by SDL
/// </summary>
/// <returns></returns>
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

/// <summary>
/// clears out the text
/// </summary>
void Keyboard::EmptyText()
{
  text.clear();
};

/// <summary>
/// tells SDL to stop cheking for typing events
/// </summary>
/// <param name="clear"></param>
void Keyboard::StopBuildText(bool clear)
{
  SDL_StopTextInput();
  if (clear)
    text.clear();
  _input = false;
};

/// <summary>
/// starts telling SDL to check for keyboard typing events
/// </summary>
void Keyboard::StartBuildText()
{
  SDL_StartTextInput();
  _input = true;
};

/// <summary>
/// builds the text using events
/// and check when a letter is needed to be deleted
/// </summary>
/// <param name="event"></param>
void Keyboard::BuildText(SDL_Event event)
{
  if (!_input)
    return;

  if (event.type == SDL_TEXTINPUT && text.size() < LIMIT)
    text += event.text.text;

  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE) 
    text += '\b';

  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
      text += ' ';
};

/// <summary>
/// gets the current key array and check if any key was pressed
/// </summary>
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
