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
  void Update();

  void OpenGame();
  void CloseGame();

  PopUpWindow SetUpRandTab(SDL_Texture* tex);
  PopUpWindow& GetPopUpWindow();
private:
  void Rungame();
  void RunHomeScreen();

  Audio* _audio;
  PopUpWindow _tab;
  WindowText _winText;
  SDL_Event ev;

  bool _onWelcomeScreen = true;//ik the that the welcomescreen opens first
  bool _isGameOpen = false;//the game opens later
};


//
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
