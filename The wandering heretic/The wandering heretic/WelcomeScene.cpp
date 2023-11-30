#include "WelcomeScene.hpp"

#include "RenderWindow.hpp"

WelcomeScene::WelcomeScene(SDL_Texture* tex, const char* fontpath, int textSize)
  :_bg(NULL), _winText(NULL), _keyPressed(false)
{
  RenderWindow* window = RenderWindow::GetRenderWindow();
  tex = window->LoadTexture("Assets/backround_pic.png");

  SDL_Rect rect;
  rect.x = 0; rect.y = 0;
  RenderWindow::GetWidthHeight(rect.w, rect.h);
  _bg = new Square(tex, rect, rect);

  _winText = new WindowText(fontpath, textSize);
  _winText->SetText("Press any key to continue...");
};

WelcomeScene::~WelcomeScene()
{
  delete _bg, _winText;
};

/// <summary>
/// the update function
/// </summary>
void WelcomeScene::Update() {
  Keyboard* keyboard = Keyboard::GetKeyboard();
    if (keyboard->IsKeyPressed())
      _keyPressed = true;

    RenderWindow* window = RenderWindow::GetRenderWindow();
    window->Render(_bg);

    //we know that the background image is the size of the entire screen
    int w = _bg->GetDstRect()->w, h = _bg->GetDstRect()->h;

  _winText->SetCharacterSize(40);
  _winText->DisplayText(Vector2i( w / 2, h - 48), RGBA(0, 0, 0, 255));
}

/// <summary>
/// return true if a key has been pressed while this window is open
/// </summary>
/// <returns></returns>
bool WelcomeScene::IsKeyPressed()
{
  return _keyPressed;
};

/// <summary>
/// sets the key pressed var to value recived
/// </summary>
/// <param name="keyPressed">booo value</param>
void WelcomeScene::SetKeyPressed(bool keyPressed)
{
  _keyPressed = keyPressed;
};
