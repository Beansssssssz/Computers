#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#define CHANNELS_COUNT 1

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

  //the mix chunk is an sdl struct which is respinsible for doing audio
  Mix_Chunk** _sound; //there are 2 paths(music and effects)
  bool* _paused; //there are 2 bools(music and effect)
};
