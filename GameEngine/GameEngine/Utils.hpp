#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


namespace utils {
  /// <summary>
  /// Evaluates how long the program is running.
  /// </summary>
  /// <returns>A float represting the amount of time that passed.</returns>
  inline float TimeRunning() {//inline means you can write the code in an header file.
    float t = SDL_GetTicks64();
    t *= 0.001f;

    return t;
  }

  /// <summary>
  /// Returns the current numbers of frams per sec by calc the number
  /// of times the cpu has ticked in nanosec.
  /// </summary>
  /// <param name="start">the amount of times the cpu ticked since the start of the game loop current loop.</param>
  /// <returns>The current number of FPS.</returns>
  inline int GetFPS(float start) {
    Uint64 end = SDL_GetPerformanceCounter();//get the timer inside the cpu in nanosecond.

    float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    std::cout << "Current FPS: " << int(1.0f / elapsed) << std::endl;

    return int(1.0f / elapsed);
  }

  /// <summary>
  /// Caps the FPS at the number you choose by using SDL_Delay and
  /// the cpu ticks.
  /// </summary>
  /// <param name="start">the amount of times the cpu ticked since the start of the game loop current loop</param>
  /// <param name="maxFPS">The maximum amount of fps the programs runs at.</param>
  inline void CapFPS(float start, int maxFPS) {
    
    Uint64 end = SDL_GetPerformanceCounter();

    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    float delay = 1000.0f / maxFPS;

    //a fail safe incase of a lage spike causing the the final value resulting in a neg val causing a crash
    if(delay - elapsedMS > 0)
      SDL_Delay(floor(delay - elapsedMS));
    //delay-elapsedMS is there incase of losing frames due to loading times in the pc.
  }
}
