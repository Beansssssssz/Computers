#pragma once

#include "Audio.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"
#include "WelcomeScene.hpp"
#include "HomeScene.hpp"

enum class Scenes
{
  welcome,
  home,
  game
};

/// <summary>
/// the class that manages the game
/// </summary>
class GameManager {
public:
  GameManager();
  ~GameManager();
  bool Update();

  bool UpdateWelcomeScene();
  bool UpdateHomeScene();
  bool UpdateGameScene();

  //PopUpWindow SetUpRandTab(SDL_Texture* tex);
private:

  Scenes _currentScene = Scenes::welcome;//You always start at the welcome Scene

  WelcomeScene* _wcScene;
  HomeScene* _HomeScene;
  WelcomeScene* _gameScreen;
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
