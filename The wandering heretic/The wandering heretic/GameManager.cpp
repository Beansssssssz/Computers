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
  if(_wcScene != nullptr)
    delete _wcScene;

  if(_homeScene != nullptr)
    delete _homeScene;

  if(_gameScene != nullptr)
    delete _gameScene;

  delete _settings;
};

/// <summary>
/// updates the current Scene of the window(welcome, home and game)
/// also updates the settings window if needed
/// </summary>
/// <returns>
/// returns true if the game is still running.
/// otherwise returns false
/// </returns>
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
    delete _gameScene;
    _gameScene = nullptr; //only from the game can you quit
    _wcScene = new WelcomeScene();

    _currentScene = Scenes::welcome;
    _settings->SetTabOpen(false);
    RenderWindow::GLOBAL_SETTING_OPEN = false;
  }

  return true;
};

/// <summary>
/// checks if a u need to go the HomeScene
/// if yes then it deleted the WelcomeScne
/// then create a new object of the HomeScene
/// </summary>
void GameManager::UpdateWelcomeScene()
{
  if (_wcScene->Update()) {
    delete _wcScene;
    _wcScene = nullptr;

    _currentScene = Scenes::home;
    _homeScene = new HomeScene;
  }
}

/// <summary>
/// Updates the HomeScene
/// can open up settings
/// when switched to the game it delete homeScene object
/// and creates a new GameScene object
/// </summary>
/// <returns>
/// true if the user has not tried quitting the window
/// otherwise returns false
/// </returns>
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
/// Updates the GameScene
/// can open up settings
/// when switched to the home it delete homeScene object
/// and creates a new HomeScene object
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
    _gameScene = nullptr;
    _homeScene = new HomeScene();
    break;

  default:
    break;
  }
}
