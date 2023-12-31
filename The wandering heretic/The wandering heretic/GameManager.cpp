#include "GameManager.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"

GameManager::GameManager()
  :_wcScene(NULL), _gameScreen(NULL), _HomeScene(NULL)
{
  _wcScene = new WelcomeScene();
  _HomeScene = new HomeScene();
  _gameScreen = new GameScene();

  _settings = Settings::CreateSettings();
};

GameManager::~GameManager()
{
  delete _wcScene, _gameScreen, _HomeScene
    ,_settings;
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
  _settings->Update(_currentScene != Scenes::home);
  return true;
};

/// <summary>
/// checks if a u need to go into
/// the home Scene
/// </summary>
void GameManager::UpdateWelcomeScene()
{
  if (_wcScene->Update()){
    _currentScene = Scenes::home;
    //delete _wcScene;
  }
}

/// <summary>
/// Updates the Home Scene with the correct happings
/// </summary>
/// <returns></returns>
bool GameManager::UpdateHomeScene()
{
  int ret = _HomeScene->Update();
  if (ret == (int)HomeButtons::Play) {
    _currentScene = Scenes::game;
    //delete _HomeScene;
  }

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
  _gameScreen->Update();
  return true;
}
