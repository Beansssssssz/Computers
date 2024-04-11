//including my own libs
#include "GameManager.hpp"
#include "SignUp.hpp"
#include "SignIn.hpp"

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;
Audio* Audio::_audioInstance = NULL;

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

  GameManager gm;
  SignUp* signUp = new SignUp({ 50, 50 }, { 100, 100 }, 100);
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

    //if (running && !gm.Update())//if the game is not going to be closed from events
    //  running = false;

    //signUp->Update();
    signin->Update();

    window->Display();

    utils::CapFPS(start, 60);
  };
  delete signUp;
  delete signin;


  //deleting singletons
  delete window;
  delete mouse;
  delete keyboard;
  delete audio;

  //quit sdl services
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
};

/*
TODO
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
  //add a button that is the finish button
  -> saves the current strings and throws an error if needed


  //ADD SIGN IN OR SIGN UP TO menu


  3.  add a finish line and an animation for it

  4. add a boss type moster which has diffrante health size and damage
     save as a var in the json file

  5. add in the hub a shop

  6. shop does what
*/
