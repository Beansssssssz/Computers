#pragma once

#include "Audio.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"

/// <summary>
/// the class that manages the game
/// </summary>
class GameManager {
public:
  GameManager(SDL_Texture* tex, const char* font);
  void Update(RenderWindow* window);
  PopUpWindow SetUpRandTab(SDL_Texture* tex);

  PopUpWindow& GetPopUpWindow();

private:
  Audio* _audio;
  PopUpWindow _tab;
  WindowText _winText;
};



//
///*
//
//
////Text Input Text
//{
//  if (keyboard.GetKeyArray()[SDL_SCANCODE_B] || listen) {
//    listen = true;
//    keyboard.StartBuildText();
//  }
//  if (keyboard.GetKeyArray()[SDL_SCANCODE_X] && listen) {
//    listen = false;
//    keyboard.StopBuildText(false);
//  }
//}
//
//winText.SetText(keyboard.GetText());
//winText.DisplayText(&window, Vector2i(500, 500), RGBA(0, 0, 0, 0));
//
//*/
