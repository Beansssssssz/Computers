#pragma once

#include "Audio.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"
#include "WelcomeScreen.hpp"

/// <summary>
/// the class that manages the game
/// </summary>
class GameManager {
public:
  GameManager(SDL_Texture* tex, const char* font);
  ~GameManager();
  void Update();

  void OpenGame();
  void CloseGame();

  PopUpWindow SetUpRandTab(SDL_Texture* tex);
private:
  void Rungame();
  void RunHomeScreen();

  Audio* _audio;

  bool _onWelcomeScreen = true;//ik the that the welcomescreen opens first
  bool _isGameOpen = false;//the game opens later

  WelcomeScreen* _wcScreen;
  WelcomeScreen* _homeScreen;
  WelcomeScreen* _gameScreen;
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
