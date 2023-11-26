#include "WelcomeScreen.hpp"

#include "RenderWindow.hpp"
#include "Utils.hpp"

WelcomeScreen::WelcomeScreen(SDL_Texture* buttonsTex, Vector2i exitPos, Vector2i StartPos)
  :_btnExit(NULL), _btnStart(NULL)
{
  int w, h;
  RenderWindow::GetWidthHeight(w,h);
  w /= 10;
  h /= 10;
  //_btnExit = new Button();
};

