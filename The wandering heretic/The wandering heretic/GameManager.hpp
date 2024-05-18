#pragma once

#include "WelcomeScene.hpp"
#include "HomeScene.hpp"
#include "GameScene.hpp"
#include "Setting.hpp"

enum class Scenes {
  welcome,
  home,
  game
};

 class GameManager {
public:
  GameManager();
  ~GameManager();

  bool Update();

  void UpdateWelcomeScene();
  bool UpdateHomeScene();
  void UpdateGameScene();

private:
  Scenes _currentScene = Scenes::welcome;//You always start at the welcome Scene

  WelcomeScene* _wcScene;
  HomeScene* _homeScene;
  GameScene* _gameScene;

  Settings* _settings;
};
