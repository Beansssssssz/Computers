//including my own libs
#include "GameManager.hpp"
#include <vector>

//initializing singletons
RenderWindow* RenderWindow::_windowPtr = NULL;
Mouse* Mouse::_mousePtr = NULL;
Keyboard* Keyboard::_keyboardPtr = NULL;
Audio* Audio::_audioInstance = NULL;


//std::vector<Button*> CreateVector();

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

  bool running = true;
  SDL_Event event;

  std::vector<Button*> vec = CreateVector();

  //starting the main loop
  while (running) {
    Uint64 start = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;

      keyboard->BuildText(event);
    }
    if (!window->IsWindowFocused())
      continue;

    window->Clear();

    mouse->Update();
    keyboard->Update();

    if (running && !gm.Update())//if the game is not going to be closed from events
      running = false;

    for (Button* btn : vec)
    {
      btn->Update();
      window->Render((Square*)btn);
    }

    if (mouse->GetPressed() == MouseButtons::mbl) {
      int x, y, w = 32, h = 32;
      Vector2i pos = mouse->GetPos();
      x = pos.x;
      y = pos.y;
      SDL_Rect dst = { x, y, h, w },
        src = { 0, 0, w, h };
      Button* btn = new Button("Assets/ground_grass1.png", src, dst);
      vec.push_back(btn);
    }

    window->Display();

    utils::CapFPS(start, 60);
  };

  vec.empty();

  //deleting singletons
  delete window, mouse, keyboard, audio;

  //quit sdl services
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  std::cin.get();
  return 0;
};

std::vector<Button*> CreateVector() {
  std::vector<Button*> vec;
  std::string path = "Assets/ground_grass1.png";
  SDL_Rect dst, src;

  //
  dst = SDL_Rect{ 0, 0, 32,32 };
  src = SDL_Rect{ 0, 0, 32, 32 };

  Button* btn = new Button(path.c_str(), src, dst);
  vec.push_back(btn);

  //
  dst = SDL_Rect{ 32, 0, 32 ,32 };
  src = SDL_Rect{ 0, 0, 32, 32 };

  btn = new Button(path.c_str(), src, dst);
  vec.push_back(btn);

  //
  dst = SDL_Rect{ 64, 0, 32, 32 };
  src = SDL_Rect{ 0, 0, 32, 32 };

  btn = new Button(path.c_str(), src, dst);
  vec.push_back(btn);

  return vec;
}

/*
TODO
now:
//parse and unparse array of objects
how to do -> create a vector of object,
then created buttons {},
in there nest each object.

//display all object into the screen
how to do -> diplay vector of rects

//add ability to select and update
how to do -> u have vector, if add square resize vector,
in deconstructor call function to save the map into json.

//in choosing an element ->
the last elemented selected(kept in a pointer) will be moved.

2.5 ->add a way to "freeze" stuff //☺





3.settings ->change colors and change quit btn tex;
4.sign in //kill me(later, wayyyy later)
5.learn sqlite3 -> how to send to main databse not local(use arduino to do it?)
6.learn socket and how to send and recive data
and how to store said data in server//use arduino to do it?
7.the game itself //fun ☺
*/
