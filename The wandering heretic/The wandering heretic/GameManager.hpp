#pragma once

#include "WelcomeScene.hpp"
#include "HomeScene.hpp"
#include "GameScene.hpp"
#include "Setting.hpp"

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

  void UpdateWelcomeScene();
  bool UpdateHomeScene();
  bool UpdateGameScene();
private:
  Scenes _currentScene = Scenes::welcome;//You always start at the welcome Scene

  WelcomeScene* _wcScene;
  HomeScene* _HomeScene;
  GameScene* _gameScreen;

  Settings* _settings;
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
