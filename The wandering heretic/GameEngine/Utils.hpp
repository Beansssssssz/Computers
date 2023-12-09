#pragma once
#include <SDL.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Button.hpp"

namespace utils {
  /// <summary>
  /// Evaluates how long the program is running.
  /// </summary>
  /// <returns>A float represting the amount of time that passed.</returns>
  inline float TimeRunning() {
    Uint64 t = SDL_GetTicks64();
    t *= 0.001f;

    return t;
  }

  /// <summary>
  /// Returns the current numbers of frams per sec by calc the number
  /// of times the cpu has ticked in nanosec.
  /// </summary>
  /// <param name="start">the amount of times the cpu ticked since the start of the game loop current loop.</param>
  /// <returns>The current number of FPS.</returns>
  inline float GetFPS(float start) {
    Uint64 end = SDL_GetPerformanceCounter();//get the timer inside the cpu in nanosecond.

    float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    return 1.0f / elapsed;
  };

  /// <summary>
  /// Caps the FPS at the number you choose by using SDL_Delay and
  /// the cpu ticks.
  /// </summary>
  /// <param name="start">the amount of times the cpu ticked since the start of the game loop current loop</param>
  /// <param name="maxFPS">The maximum amount of fps the programs runs at.</param>
  inline void CapFPS(Uint64 start, int maxFPS) {

    Uint64 end = SDL_GetPerformanceCounter();

    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    float delay = 1000.0f / maxFPS;

    //a fail safe incase of a lage spike causing the the final value resulting in a neg val causing a crash
    if (delay - elapsedMS > 0)
      SDL_Delay(floor(delay - elapsedMS));
    //delay-elapsedMS is there incase of losing frames due to loading times in the pc.
  };

  inline SDL_Color ChangeRgbaToSdlColor(RGBA color) {
    SDL_Color sdlColor;
    sdlColor.a = color.a; sdlColor.r = color.r; sdlColor.b = color.b; sdlColor.g = color.g;
    return sdlColor;
  };

  inline Button CreateButton(SDL_Texture* tex, int w, int h, Vector2i pos) {
    SDL_Rect srcRect, dstRect;
    dstRect.x = 0; dstRect.y = 0, dstRect.w = w; dstRect.h = h;
    srcRect.x = 0; srcRect.y = 0, srcRect.w = w; srcRect.h = h;
    Button button(tex, srcRect, dstRect);

    return button;
  };

  /// <summary>
  /// return a texture which is widely used in the game
  /// </summary>
  /// <param name="num">the num of the texure:
  /// 1:btn exit
  /// 2:btn play
  /// 3:grass or someshit
  /// 
  /// </param>
  /// <returns>return selcted texture or NULL if a number which does exit is selected</returns>
  inline SDL_Texture* GetTexture(int num) {
    RenderWindow* window = RenderWindow::GetRenderWindow();
    switch (num)
    {
    case 1:
      return window->LoadTexture("Assets/GUI/btnExit.png");
    case 2:
      return window->LoadTexture("Assets/GUI/btnPlay.png");
    case 3:
      break;
    };
    return NULL;
  };

  /// <summary>
  /// clamps the val so that i wont go out of bouns
  /// </summary>
  /// <param name="val">the value refrence</param>
  /// <param name="max"></param>
  /// <param name="min"></param>
  inline void Clamp(int& val, int max, int min = 0) {
    if (val > max)
      val = max;
    if (val < min)
      val = min;
  }
};
