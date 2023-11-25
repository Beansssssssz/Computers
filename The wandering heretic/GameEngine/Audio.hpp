#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class Audio
{
public:
  Audio(const char* path, int channels = 2);
  ~Audio();
  int GetVolume(int channel);
  void SetVolume(int vol, int channel);
  void ChangeMusic(const char* path, int channel);
  void PauseMusic(int channel = -1);
  void ResumeMusic(int channel = -1);

private:
  Mix_Chunk** sound;
};
