#pragma once

#include "LevelEditor.hpp"
#include "GameWorld.hpp"

#include "Button.hpp"
#include "WindowText.hpp"
#include "InputText.hpp"
#include "ChooseNumber.hpp"

#include <string>

class GameScene
{
public:
  GameScene();
  ~GameScene();

  int Update();
private:
  void LogUser();

  void CreateInputTextAreas();

  std::string _currentUser;
  Square* _bg;

  LevelEditor* _edit;//the level editor
  GameWorld* _world;

  InputText** _inText;
  ChooseNumber* ch;

  bool _logUser;
  bool _choosingLevel;
  bool _isAdmin;
};
