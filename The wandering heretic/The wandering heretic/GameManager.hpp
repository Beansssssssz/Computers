#pragma once

#include "Audio.hpp"
#include "PopUpWindow.hpp"
#include "WindowText.hpp"
#include "WelcomeScene.hpp"
#include "HomeScene.hpp"

enum class Scenes
{
  welcome,
  home,
  game
};

/// <summary>
/// the class that manages the game
/// </summary>
class GameManager {
public:
  GameManager();
  ~GameManager();
  void Update();

  Scenes& GetScenes();

  PopUpWindow SetUpRandTab(SDL_Texture* tex);
private:
  void FindCurrentScene();

  Audio* _audio;

  Scenes _currentScene = Scenes::welcome;//ik the that the WelcomeScene opens first

  WelcomeScene* _wcScene;
  HomeScene* _HomeScene;
  WelcomeScene* _gameScreen;
};


//
//{
//  if (keyboard.GetKeyArray()[SDL_SCANCODE_B] || listen) {
//    listen = true;
//    keyboard.StartBuildText();
//  }
//  if (keyboard.GetKeyArray()[SDL_SCANCODE_X] && listen) {
//    listen = false;
//    keyboard.StopBuildText(false);
//  }
//}
