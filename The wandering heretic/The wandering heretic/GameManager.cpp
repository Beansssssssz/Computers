#include "GameManager.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"

GameManager::GameManager()
  :_wcScene(new WelcomeScene()),
  _homeScene(nullptr),
  _gameScene(nullptr)
{
  _settings = Settings::CreateSettings();
};

GameManager::~GameManager()
{
  delete _wcScene;
  delete _gameScene;
  delete _homeScene;
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
    UpdateGameScene();
    break;
  }

  //settings is a universal thing so in game manager
  if (_settings->Update(_currentScene != Scenes::home)) {
    _currentScene = Scenes::welcome;
    _settings->SetTabOpen(false);
    RenderWindow::GLOBAL_SETTING_OPEN = false;
  }

  return true;
};

/// <summary>
/// checks if a u need to go into
/// the home Scene
/// </summary>
void GameManager::UpdateWelcomeScene()
{
  if (_wcScene->Update()) {
    _currentScene = Scenes::home;
    _homeScene = new HomeScene;
  }
}

/// <summary>
/// Updates the Home Scene with the correct happings
/// </summary>
/// <returns></returns>
bool GameManager::UpdateHomeScene()
{
  HomeButtons ret = (HomeButtons)_homeScene->Update();
  switch (ret)
  {
  case HomeButtons::Play:
    _currentScene = Scenes::game;

    _gameScene = new GameScene();
    delete _homeScene;
    _homeScene = nullptr;
    break;

  case HomeButtons::Settings:
    _settings->SetTabOpen(true);
    RenderWindow::GLOBAL_SETTING_OPEN = true;
    break;

  case HomeButtons::Quit:
    return false;
    break;
  }

  return true;
};

/// <summary>
/// runs the games(nothing more really)
/// </summary>
void GameManager::UpdateGameScene()
{
  GameReturnValues ret = _gameScene->Update();
  switch (ret)
  {
  case GameReturnValues::Settings:
    _settings->SetTabOpen(true);
    RenderWindow::GLOBAL_SETTING_OPEN = true;
    break;

  case GameReturnValues::Home:
    _currentScene = Scenes::home;

    delete _gameScene;
    _homeScene = new HomeScene();
    break;

  default:
    break;
  }
}

