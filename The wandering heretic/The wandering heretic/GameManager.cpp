#include "GameManager.hpp"
#include "Utils.hpp"

GameManager::GameManager(SDL_Texture* tex, const char* font)
  :_audio(NULL), _tab(SetUpRandTab(tex)), _winText(font, 24, "dsa")
{
};

void GameManager::Update(RenderWindow* window)
{
  _tab.Update(window);
  _winText.DisplayText(window, Vector2i(100, 100), RGBA(0, 0, 0, 255));
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

PopUpWindow& GameManager::GetPopUpWindow()
{
  return _tab;
};
