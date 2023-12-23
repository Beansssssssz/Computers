#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#define CHANNAELS_COUNT 2

class Audio
{
public:
  static Audio* GetAudioInstance();
  ~Audio();

  void StartMusic();
  void PlayMusic(int channel, int loop);

  int GetVolume(int channel);
  void SetVolume(int vol, int channel = -1);

  void SetMusic(const char* path, int channel, bool startPlayin = false);
  void PauseMusic(int channel = -1);
  void ResumeMusic(int channel = -1);

private:
  static Audio* _audioInstance;
  Audio();
  Mix_Chunk** _sound;

  bool* _paused;
};
