#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


namespace utils {
  /// <summary>
  /// Evaluates how long the program is running.
  /// </summary>
  /// <returns>A float represting the amount of time that passed.</returns>
  inline float TimeRunning() {//inline means you can write the code in an header file
    float t = SDL_GetTicks64();
    t *= 0.001f;

    return t;
  }

  /// <summary>
  /// Returns the current numbers of frams per sec
  /// </summary>
  /// <param name="start"></param>
  /// <returns>The current number of FPS</returns>
  inline float GetFPS(float start) {
    Uint64 end = SDL_GetPerformanceCounter();//get the timer inside the cpu in nanosecond

    float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    std::cout << "Current FPS: " << 1.0f / elapsed << std::endl;
    return 1.0f / elapsed;
  }

  /// <summary>
  /// Caps the FPS at the number you choose
  /// </summary>
  /// <param name="start"></param>
  /// <param name="maxFPS">The maximum amount of fps the programs runs at </param>
  inline void CapFPS(float start, int maxFPS) {
    Uint64 end = SDL_GetPerformanceCounter();

    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    // Cap to 60 FPS
    SDL_Delay(floor(16.666f - elapsedMS));
  }

}
