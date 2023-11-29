#include "GameManager.hpp"
#include "Utils.hpp"
#include "Keyboard.hpp"

GameManager::GameManager(SDL_Texture* tex, const char* font)
  :_audio(NULL), _wcScreen(NULL), _gameScreen(NULL), _homeScreen(NULL)
{
  _wcScreen = new WelcomeScreen("aaaaaaaaaaa", "Assets/Fonts/Sans.ttf", 24);
  _gameScreen = new WelcomeScreen("", "sans", 24);
  _homeScreen = new WelcomeScreen("", "sans", 24);
};
GameManager::~GameManager()
{
  delete _wcScreen, _gameScreen, _homeScreen, _audio;
};

void GameManager::Update()
{
  //Keyboard* keyboard = Keyboard::GetKeyboard();

  if (_isGameOpen)
    Rungame();
  else
    RunHomeScreen();
};

/// <summary>
/// the function where the game runs
/// </summary>
void GameManager::Rungame()
{
  RenderWindow* window = RenderWindow::GetRenderWindow();
  /*_tab.Update();
  _winText.DisplayText(Vector2i(100, 100), RGBA(0, 0, 0, 255));*/
};

/// <summary>
/// the function where the homescreen and
/// the press a welcomescreen runs
/// </summary>
void GameManager::RunHomeScreen()
{
  if (_wcScreen->IsKeyPressed()) {
    int w, h;
    RenderWindow::GetWidthHeight(w, h);
    //_winText.SetCharacterSize(40);
    //_winText.DisplayText(Vector2i(w / 2 , h - 48), RGBA(0, 0, 0, 255));
    return;
  }
  _wcScreen->Update();
};

/// <summary>
/// sets it so that the game will run next
/// </summary>
void GameManager::OpenGame()
{
  _isGameOpen = true;
};

void GameManager::CloseGame()
{
  _isGameOpen = false;
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
