#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class Audio
{
public:
  static Audio* GetAudioInstance();
  ~Audio();
  void PlayMusic(int channel, int loop);

  int GetVolume(int channel);
  void SetVolume(int vol, int channel);

  void SetMusic(const char* path, int channel, bool startPlayin = false);
  void PauseMusic(int channel = -1);
  void ResumeMusic(int channel = -1);

private:
  static Audio* _audioInstance;
  Audio(int channels = 2);
  Mix_Chunk** _sound;
};
