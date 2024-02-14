//including my own libs
#include "GameManager.hpp"

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

  ////singletons
  RenderWindow* window = RenderWindow::GetRenderWindowInstance();
  Mouse* mouse = Mouse::GetMouseInstance();
  Keyboard* keyboard = Keyboard::GetKeyboardInstance();
  Audio* audio = Audio::GetAudioInstance();

  GameManager gm;

  SDL_Event event;
  bool running = true;

  //the game loop
  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) 
        running = false;
      
      keyboard->BuildText(event);
    }
    /*if (!window->IsWindowFocused())
      continue;*/

    window->Clear();

    mouse->Update();
    keyboard->Update();

    if (running && !gm.Update())//if the game is not going to be closed from events
      running = false;

    window->Display();

    utils::CapFPS(start, 60);
  };
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

//make jump more smooth(like in u control the strength)
->have a check if the player still pressing
if yes then add to speed.y
else then make the var false and continue normally

//add scrolling
check if the player is too far in 1 direction
if yes then add said direction the all the Entitys in the level

//add scrolling in the editor
mouse scroll whell up -> all vector _dst.y-- (up)
mouse scroll whell down -> all vector _dst.y++ (down)
mouse shift scroll whell up -> all vector _dst.x-- (left)
mouse shift scroll whell down -> all vector _dst.y++ (right)

//create a map
->in tiled create a map for the player
//create enemy
->enemy check if player in the same y ~ish
if yes then go to enemy
maybe jump if needed


//Add settings to the RealGame

//Create the actuall Player Class(not gameEngine one)

//Go through code and fix bugs

========TODO========:

2.5 ->add a way to "freeze" stuff ->
a way to tell the mouse to stop the pressing on other buttons
or -> use the bool as a pointer or ref(ref better) and when u r updating the buttons
check if the settings is open.

3.settings ->change textures and change quit btn tex;

4.sign in -> start in the middle of the 3rd month

5.learn sqlite3 -> how to send to main databse not local(use arduino to do it?)

6.learn socket -> send struct through sockets of players to create a multiplayer game

========TRY========:
1.search for UB and fix bugs -> just play the game

2.fix the save game function in editing
*/
