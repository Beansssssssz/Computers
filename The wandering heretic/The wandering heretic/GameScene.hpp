#pragma once

#include "Button.hpp"
#include "LevelEditor.hpp"
#include "WindowText.hpp"
#include "InputText.hpp"

#include <string>

class GameScene
{
public:
  GameScene();
  ~GameScene();

  int Update();
private:
  void LogUser();

  std::string _currentUser;
  Square* _bg;

  LevelEditor* _edit;//the level editor
  InputText** _inText;

  bool _logUser;
  bool _isAdmin;
};
