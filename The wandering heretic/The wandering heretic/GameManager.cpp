#include "GameManager.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"

GameManager::GameManager()
  :_wcScene(NULL), _gameScene(NULL), _HomeScene(NULL)
{
  _wcScene = new WelcomeScene();
  _HomeScene = new HomeScene();
  _gameScene = new GameScene();

  _settings = Settings::CreateSettings();
};

GameManager::~GameManager()
{
  delete _wcScene;
  delete _gameScene;
  delete _HomeScene;
  delete _settings;
};

/// <summary>
/// returns true if the game is still running.
/// otherwise returns false
/// </summary>
/// <returns></returns>
bool GameManager::Update()
{
  int ret = 0;
  switch (_currentScene)
  {
  case Scenes::welcome:
    UpdateWelcomeScene();
    break;
  case Scenes::home:
    ret = UpdateHomeScene();
    if (!ret)
      return false;
    break;
  case Scenes::game:
    ret = UpdateGameScene();
    if (!ret)
      return false;
    break;
  }

  //settings is a universal thing so in game manager
  if (_settings->Update(_currentScene != Scenes::home)) {
    _currentScene = Scenes::welcome;
    _settings->CloseTab();
  }
  return true;
};

/// <summary>
/// checks if a u need to go into
/// the home Scene
/// </summary>
void GameManager::UpdateWelcomeScene()
{
  if (_wcScene->Update())
    _currentScene = Scenes::home;
}

/// <summary>
/// Updates the Home Scene with the correct happings
/// </summary>
/// <returns></returns>
bool GameManager::UpdateHomeScene()
{
  int ret = _HomeScene->Update();
  if (ret == (int)HomeButtons::Play) 
    _currentScene = Scenes::game;

  else if (ret == (int)HomeButtons::Settings)
    _settings->OpenTab();

  else if (ret == (int)HomeButtons::Quit)
    return false;

  return true;
};

/// <summary>
/// TODO
/// </summary>
/// <returns>true if game is running false if quitting game</returns>
bool GameManager::UpdateGameScene()
{
  if (_gameScene->Update())
    _settings->OpenTab();
  return true;
}
