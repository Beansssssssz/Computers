#include "GameManager.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"

GameManager::GameManager()
  :_audio(NULL), _wcScene(NULL), _gameScreen(NULL), _HomeScene(NULL)
{
  _wcScene = new WelcomeScene("Assets/Fonts/font.otf", 24);
  _HomeScene = new HomeScene();
  _gameScreen = new WelcomeScene("sans", 24);
};
GameManager::~GameManager()
{
  delete _wcScene, _gameScreen, _HomeScene, _audio;
};

bool GameManager::Update()
{
  int ret = 0;
  switch (_currentScene)
  {
  case Scenes::game:
    break;
  case Scenes::home:
    ret = _HomeScene->Update();
    return ret != (int)HomeButtons::Quit;
    break;
  case Scenes::welcome:
    _wcScene->Update();
    break;
  }
  FindCurrentScene();
  return true;
};

/// <summary>
/// sets it so that the game will run next
/// </summary>
Scenes& GameManager::GetScenes()
{
  return _currentScene;
}

void GameManager::FindCurrentScene()
{
  if (_wcScene->IsKeyPressed())
    _currentScene = Scenes::home;
};

PopUpWindow GameManager::SetUpRandTab(SDL_Texture* tex)
{
  SDL_Rect rect1;
  rect1.x = 300; rect1.y = 300, rect1.w = 500; rect1.h = 500;
  RGBA color(40, 80, 100, 160);
  Button button1 = utils::CreateButton(tex, 113, 114, Vector2i(2, 1));

  PopUpWindow tab(button1, rect1, color, true);
  return tab;
};
