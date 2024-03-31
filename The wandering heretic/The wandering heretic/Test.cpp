//including my own libs
#include "GameManager.hpp"
#include "TextSquare.hpp"

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;
Audio* Audio::_audioInstance = NULL;

bool IsPasswordStrong(std::string password);
bool IsLetterSpecial(const char& letter);


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
  TextSquare text({50, 50, 200, 30}, 1, 12, 50);

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

    text.Update();
    //if (running && !gm.Update())//if the game is not going to be closed from events
    //  running = false;

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


static bool IsMailValid(std::string mail) {
  int startDomainName = mail.find('@');
  const char* domainName = mail.substr(startDomainName, mail.size()).c_str();

  const char* allDomainNames[] = { "gmail.com", "nomishemer.ort.org" };
  constexpr char DOMMAIN_COUNT = 2;

  for (int i = 0; i < DOMMAIN_COUNT; i++)
    if (!strcmp(domainName, "gmail.com"))
      return false;

  return true;
}



static bool IsPasswordStrong(std::string pass) {
  if (pass.size() < 8)
    return false;

  bool upper = false;
  bool lower = false;
  bool number = false;
  bool special = false;

  for (const char& letter : pass) {
    if (letter >= 'A' && letter <= 'Z')
      upper = true;
    else if (letter >= 'a' && letter <= 'z')
      lower = true;
    else if (letter >= '0' && letter <= '9')
      number = true;
    else if(IsLetterSpecial(letter))
      special = true;
  }
  
  return upper & lower & number & special;
}

static bool IsLetterSpecial(const char& letter) {
  const char* allLetters = "~!@#$%^&*()-_+={}[]|/:;<>,?";
  int length = sizeof(allLetters); //its char and char is size of 1

  for (int i = 0; i < length; i++)
    if (allLetters[i] == letter)
      return true;
  return false;
}

/*
TODO
========NOW========:
//add sign in as an option
->  create 2 white squares
    once u press inside a white sqaure u cant type inside
    in order to exit u can press anywhere outside the sqaure or press enter
    add a button which is confirme.


//add enemy to the world
-> damage is done by touching

//create the actuall Player Class(not gameEngine one)
  actuall player creation
  actuall gifs
  attacks and health

//when u reach a certin point in the world then u finish the level mario style,
then sends u back into the level choosing

========TODO========:

1.sign in -> start in the middle of the 3rd month

3.add a way to "freeze" stuff ->
a way to tell the mouse to stop the pressing on other buttons
or -> use the bool as a pointer or ref(ref better) and when u r updating the buttons
check if the settings is open.

4.add a way to delete blocks in the editing world 

6. add more a more smarter enemy which can attack and shoot at u

========TRY========:
1.search for UB and fix bugs -> just play the game

2.fix the save game function in editing

3.make jump more smooth(like hollow knight smooth)

4.check my scrolling (was very very scuffed)
*/


/*
  roadmap to finish everything:
  1.  finish sign in
  2.  add an hub
  3.  add a finish line and an animation for it
  4. create 10 big levels?????, each level has a boss and a finish line which returns u to the hub
  5. add in the hub a shop
  6. shop does what??????????

*/
