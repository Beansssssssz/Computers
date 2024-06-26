#include "Setting.hpp"

#include <iostream>
#include "RenderWindow.hpp"

Settings::Settings(Button* btnExit, SDL_Rect rect, SDL_Color color)
  :Settings::PopUpWindow(btnExit, rect, color), _marginY(0),
  _btnEffect(NULL), _btnMusic(NULL), _slider(NULL),
  _musicOn(true), _effectOn(true), _btnQuit(NULL)
{
  CreateText();
  CreateSlider();
  CreateQuitButton();
};

Settings::~Settings()
{
  delete _btnMusic;
  delete _btnEffect;
  delete _btnQuit;
  delete _slider;
}

/// <summary>
/// updates the settings menu
/// </summary>
/// <param name="NeedExitGame">if true then displays the quit game button
/// otherwise does not</param>
/// <returns>true or false,true means quit</returns>
bool Settings::Update(bool NeedExitGame)
{
  if (!_tabOpen) 
    return false;

  Settings::PopUpWindow::Update();
  if (!this->GetTabOpen()) {
    RenderWindow::GLOBAL_SETTING_OPEN = false;
    return false;
  }

  UpdateText();
  UpdateMusic();

  if (NeedExitGame)
    return UpdateQuitBtn();

  return false;
};

/// <summary>
/// updates all the music elements in the class
/// </summary>
void Settings::UpdateMusic()
{
  Audio* audio = Audio::GetAudioInstance();
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  //checking if buttons are released(pressed the not pressed)
  if (_btnMusic->GetIsReleased())
  {
    audio->SetMusicState(_musicOn, 0);
     _musicOn = !_musicOn;

    //change image
    std::string path = "Assets/GUI/";
    if (_musicOn)
      path += "on_button";
    else
      path += "off_button";
    path += ".png";

    _btnMusic->SetTexture(path.c_str());
  }

  if (_btnEffect->GetIsReleased())
  {
    _effectOn = !_effectOn;
    //audio->SetMusicState(_effectOn, 1);

    //change image
    std::string path = "Assets/GUI/";
    if (_effectOn)
      path += "on_button";
    else
      path += "off_button";
    path += ".png";

    _btnEffect->SetTexture(path.c_str());
  }

  //updating the buttons
  _btnMusic->Update();
  _btnEffect->Update();

  //redering the buttons
  window->Render((Square*)_btnMusic);
  window->Render((Square*)_btnEffect);

  _slider->Update();
  audio->SetVolume(_slider->GetValue(), 0);
};

/// <summary>
/// updates the text
/// </summary>
void Settings::UpdateText()
{
  _musicText->DisplayText();
  _effectText->DisplayText();
}

/// <summary>
/// updates the quit button
/// returns 1 or true if btn is pressed
/// otherwise returns 0 or false
/// </summary>
/// <returns></returns>
int Settings::UpdateQuitBtn()
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();

  _btnQuit->Update();
  window->Render((Square*)_btnQuit);

  if (_btnQuit->GetIsPressed())
    return 1;

  return 0;
};

/// <summary>
/// creates the text for the specefic buttons
/// </summary>
void Settings::CreateText() {
  _musicText = new WindowText();
  _effectText = new WindowText();

  _musicText->SetText("music: ");
  _effectText->SetText("effects: ");

  CreateButtons();//is here becuse is saves cycles creating the text first
  //then changing the position only once(not necessary its just optimization)

  SDL_Rect tempRect = *_btnMusic->GetDstRect();

  ///music text
  int x = tempRect.x - _musicText->GetTextWidth() * 2 - MARGIN;
  int y = tempRect.y + _musicText->GetTextHeight();
  _musicText->SetPos(Vector2i{x, y});

  //effect text
  y = _btnEffect->GetDstRect()->y + _effectText->GetTextHeight();
  _effectText->SetPos(Vector2i{x, y});
}

/// <summary>
/// Creates the buttons
/// </summary>
void Settings::CreateButtons(int marginx, int marginy) {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* texMusic = window->LoadTexture("Assets/GUI/on_button.png");
  SDL_Texture* texEffect = window->LoadTexture("Assets/GUI/on_button.png");

  int w, h;
  SDL_QueryTexture(texMusic, NULL, NULL, &w, &h);
  SDL_Rect src{ 0, 0, w, h }, dst{ 0, 0, w, h };//{x, y, w, h)
  SDL_Rect temp = PopUpWindow::GetRect();

  CalculateMargin(marginy, temp.h);

  //create Music Button:
  dst.x = ( temp.x  + temp.w + _effectText->GetTextWidth()) / 2 ;
  dst.y = temp.y + marginy;
  _btnMusic = new Button(texMusic, src, dst);

  ///Create Effect Button:
  dst.y += marginy + _marginY;

  _btnEffect = new Button(texEffect, src, dst);
};

/// <summary>
/// Creates the Slider
/// </summary>
void Settings::CreateSlider(int marginx, int w, int h) {
  SDL_Rect rect = Settings::GetRect();

  int pos1 = rect.x + MARGIN;
  int pos2 = rect.x + rect.w - MARGIN;

  rect = *_btnEffect->GetDstRect();

  int x = (pos1 + pos2) / 2;
  int y = rect.y + _marginY + (rect.h / 2) - (h / 2);

  SDL_Rect dst{ x, y, w, h };
  SDL_Color color{ 0,0,0,255 };

  _slider = new Slider(dst, pos1, pos2, color, 15);
}

/// <summary>
/// creates the quit button
/// </summary>
void Settings::CreateQuitButton() {
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/on_button.png");

  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);
  SDL_Rect src{ 0, 0, w, h }, dst{ 0, 0, w, h };//{x, y, w, h)
  SDL_Rect temp = *_btnEffect->GetDstRect();

  dst.x = temp.x ;
  dst.y = _slider->GetRect().y + _marginY;

  _btnQuit = new Button(tex, src, dst);
}

/// <summary>
/// creates a setting class
/// </summary>
/// <param name="marginx"></param>
/// <param name="marginy"></param>
/// <returns></returns>
Settings* Settings::CreateSettings(int marginx, int marginy)
{
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  SDL_Texture* tex = window->LoadTexture("Assets/GUI/Xbtn.png");
  int w, h;
  SDL_QueryTexture(tex, NULL, NULL, &w, &h);
  Button* btn = new Button(tex, { 0,0,w,h }, { 0,0,w,h });

  SDL_Rect rect;
  RenderWindow::GetWidthHeight(w, h);
  rect.x = marginx;
  rect.y = marginy;
  rect.w = w - marginx * 2;
  rect.h = h - marginy * 2;

  SDL_Color _color{255, 100, 100, 100 };

  return new Settings(btn, rect, _color);
}

/// <summary>
/// caculates teh margin between the buttons
/// </summary>
/// <param name="margin"></param>
/// <param name="overall"></param>
void Settings::CalculateMargin(int margin, int overall)
{
  _marginY = (overall - margin * 2) / 4;
};
