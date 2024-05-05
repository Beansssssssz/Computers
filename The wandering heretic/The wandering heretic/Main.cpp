//including my own libs
#include "GameManager.hpp"
#include "SignUp.hpp"
#include "SignIn.hpp"

//initializing a global variable 
bool RenderWindow::GLOBAL_SETTING_OPEN = false;

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = nullptr;
Mouse* Mouse::_mousePtr = nullptr;
Keyboard* Keyboard::_keyboardPtr = nullptr;
Audio* Audio::_audioInstance = nullptr;
Server* Server::_serverPtr = nullptr;

int main(int argc, char* argv[]) {
  //initializing the libraries
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init failed. SDL ERROR: %s", SDL_GetError());

  if (IMG_Init(IMG_INIT_PNG) == 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG Init failed. IMG ERROR: %s", IMG_GetError());

  if (TTF_Init() != 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_ttf: %s", TTF_GetError());

  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) == 0)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_mixer: %s", Mix_GetError());

  //singletons
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Audio* audio = Audio::GetAudioInstance();
  Server* server = Server::GetServerInstance();

  GameManager* gm = new GameManager();

  SDL_Event event;
  bool running = true;
  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }

      mouse->SetScrollYFromEvent(event);
      keyboard->BuildText(event);
    }
    /*if (!window->IsWindowFocused())
      continue;*/

    window->Clear();

    mouse->Update();
    keyboard->Update();

    if (running && !gm->Update())
      running = false;

    window->Display();

    utils::CapFPS(start, 60);
  };

  //deleting the game manager aka the game itselfs
  delete gm;

  //deleting singletons
  delete window;
  delete mouse;
  delete keyboard;
  delete audio;
  delete server;
  
  //quit sdl services
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
};

/* 
========NOW========:
//in gamePlayer make him die when hit

//add a "finishLine", when the player touches the finish line the player will be taken to the home screen
today: when player touches the finishLine take him to the home
-> add animation
-> add lock to levels based on user
-> add more levels

========TRY========:
0. bug -> when pressing done button in signIn it also presses settings

1. bug -> idk smth with the enemy attack gif

2. bug -> when enemy attack in corner he is stuck attacking

3. bug -> fix the save game function in editing
*/
