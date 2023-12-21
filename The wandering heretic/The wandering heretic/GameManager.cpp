#include "GameManager.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"

GameManager::GameManager()
  :_wcScene(NULL), _gameScreen(NULL), _HomeScene(NULL)
{
  _wcScene = new WelcomeScene("Assets/Fonts/font.otf", 24);
  _HomeScene = new HomeScene();
  _gameScreen = new WelcomeScene("sans", 24);
};

GameManager::~GameManager()
{
  delete _wcScene, _gameScreen, _HomeScene;
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
    return UpdateHomeScene();
    break;
  case Scenes::game:
    return UpdateGameScene();
    break;
  }
  return true;
};

/// <summary>
/// Always returns false
/// </summary>
/// <returns></returns>
bool GameManager::UpdateWelcomeScene()
{
  int  ret = _wcScene->Update();
  if (ret == 1)
    _currentScene = Scenes::home;

  return false;
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
    delete _HomeScene;
  }

  if (ret == (int)HomeButtons::Settings)
    std::cout << "kill me\n" << std::endl;

  return ret != (int)HomeButtons::Quit;
};

/// <summary>
/// TODO
/// </summary>
/// <returns></returns>
bool GameManager::UpdateGameScene()
{
  return false;
}

//PopUpWindow GameManager::SetUpRandTab(SDL_Texture* tex)
//{
//  SDL_Rect rect1;
//  rect1.x = 300; rect1.y = 300, rect1.w = 500; rect1.h = 500;
//  SDL_Color color{ 40, 80, 100, 160 };
//  Button button1 = utils::CreateButton(tex, 113, 114, Vector2i(2, 1));
//
//  PopUpWindow tab(button1, rect1, color, true);
//  return tab;
//};
