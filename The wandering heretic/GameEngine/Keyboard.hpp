#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#define LIMIT 30

class Keyboard
{
public:
  static Keyboard* GetKeyboardInstance();
  ~Keyboard();

  Uint8* GetKeyArray();
  std::string GetText();
  void SetText(std::string str);
  void EmptyText();

  void StopBuildText(bool clear = true);
  void StartBuildText();
  void BuildText(SDL_Event event);

  void Update();
  bool IsKeyPressed();

private:
  Keyboard();
  static Keyboard* _keyboardPtr;

  Uint8* _keysArray;//the key array given by sdl(deleted in SDL_Quit())
  std::string text;
  bool _input;
  bool _keyPressed;
};
