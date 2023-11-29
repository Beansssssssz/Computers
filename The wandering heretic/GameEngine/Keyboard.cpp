#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Keyboard.hpp"

Keyboard::Keyboard()
  :keysArray(NULL), _input(false), _keyPressed(false)
{};

Keyboard* Keyboard::GetKeyboard()
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
{};

Uint8* Keyboard::GetKeyArray()
{
  return keysArray;
}

std::string Keyboard::GetText()
{
  return text;
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
  if (event.key.state == SDL_PRESSED)
    _keyPressed = true;
  else if(event.key.state == SDL_RELEASED)
    _keyPressed = false;

  if (!_input)
    return;

  if (event.type == SDL_TEXTINPUT) 
    text += event.text.text;
  
  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
    if(text.size() > 0)
      text.pop_back();
};

void Keyboard::Update()
{
  _keyPressed = false;
  SDL_PumpEvents();
  keysArray = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
  for (int i = 0; i < 250; i++)//all the keys on the keyboard
    if (keysArray[i])
      _keyPressed = true;
};

/// <summary>
/// return true of any key press is happing
/// otherwise returns false
/// </summary>
bool Keyboard::IsKeyPressed()
{
  return _keyPressed;
};
