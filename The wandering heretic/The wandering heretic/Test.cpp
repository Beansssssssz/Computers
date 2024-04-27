//including my own libs
#include "GameManager.hpp"
#include "SignUp.hpp"
#include "SignIn.hpp"

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

  GameManager gm;
  SignUp* signup = new SignUp({ 50, 50 }, { 100, 100 }, 100);
  SignIn* signin = new SignIn({ 50, 50 }, { 100, 100 }, 100);

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

    if (running && !gm.Update())//if the game is not going to be closed from events
      running = false;

    //if (signup->Update()) {
    //  std::string email, username, password;
    //  break;
    //}
    
    //if (signin->Update()) {
    //  std::string email, password;
    //  break;
    //}

    window->Display();

    utils::CapFPS(start, 60);
  };


  delete signup;
  delete signin;

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
* VACATION:
* user already exist
*
* 
* Add sign in and sign up to the menu 
* add enemy to the world
 
========NOW========:
//fix WindowText:
  add flashing cursor -> cursor has a bug in which is doest go back all the way

//add enemy to the world
-> damage is done by touching

//create the actuall Player Class(not gameEngine one)
  actuall player creation
  actuall gifs
  attacks and health

//when u reach a certin point in the world then u finish the level mario style,
then sends u back into the level choosing

========TODO========:

1.add a way to "freeze" stuff ->
a way to tell the mouse to stop the pressing on other buttons
or -> use the bool as a pointer or ref(ref better) and when u r updating the buttons
check if the settings is open.

2.add a way to delete blocks in the editing world

========TRY========:
1.search for UB and fix bugs -> just play the game

2.fix the save game function in editing

3.make jump more smooth(like hollow knight smooth)

4.check my scrolling (was very very scuffed)
*/


/*
  roadmap to finish everything:
  2. add sign in and sign up to menu

  3.  add a finish line and an animation for it

  5. add in the hub a shop
*/
