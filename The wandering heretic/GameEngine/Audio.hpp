#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#define CHANNAELS_COUNT 1

class Audio
{
public:
  static Audio* GetAudioInstance();
  ~Audio();
  void StartMusic();

  int GetVolume(int channel);
  void SetVolume(int vol, int channel = -1);

  void SetMusic(const char* path, int channel, int loops = -1,bool startPlayin = false);

  void SetMusicState(bool state, int channel = -1);
  void PauseMusic(int channel = -1);
  void ResumeMusic(int channel = -1);

  const int MAX_VAL = 128;
private:
  static Audio* _audioInstance;
  Audio();
  Mix_Chunk** _sound;

  bool* _paused;
};
