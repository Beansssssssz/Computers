#include "WelcomeScene.hpp"

#include "RenderWindow.hpp"

WelcomeScene::WelcomeScene()
  :_bg(NULL), _winText(NULL), _keyPressed(false)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/Backgrounds/home_background.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  _bg = new Square(tex, rect, rect);

  _winText = new WindowText();
  _winText->SetText("Press any key to continue...");
};

WelcomeScene::~WelcomeScene()
{
  delete _bg;
  delete _winText;
};

/// <summary>
/// checks if the player has pressed any key
/// if yes then it moves to the homeScene
/// </summary>
bool WelcomeScene::Update() {
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();

  bool ret = false;
  if (keyboard->IsKeyPressed())
    _keyPressed = true;
  else if (_keyPressed) {
    ret = true;
    _keyPressed = false;
  }

  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  window->Render(_bg);

  //we know that the background image is the size of the entire screen
  int w = _bg->GetDstRect()->w, h = _bg->GetDstRect()->h;

  SDL_Color color{ 0, 0, 0, 255 };

  _winText->SetCharacterSize(40);
  _winText->DisplayText(Vector2i(w / 2 - _winText->GetTextWidth() / 2, h - 48), color);

  return ret;
}
