#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#include "Audio.hpp"


//channel 0 is for backround music/boss fights
//channel 1 is for pop effect(npc or such)
//channel 2 is cause for future 
Audio::Audio(const char* path, int channels)
{
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, channels, 1024);
  sound = new Mix_Chunk* [channels];

  sound[0] = Mix_LoadWAV(path);

  if (sound == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error sound failed to load: %s", Mix_GetError());

  int channel =  Mix_PlayChannel(-1, sound[0], -1);
  if(channel == -1)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error sound failed to play: %s", Mix_GetError());
};

Audio::~Audio()
{
  Mix_CloseAudio();
};

int Audio::GetVolume(int channel)
{
  return Mix_VolumeChunk(sound[channel], -1);
};

void Audio::SetVolume(int vol, int channel)
{
  Mix_VolumeChunk(sound[channel], vol);
};

void Audio::ChangeMusic(const char* path, int channel)
{
  sound[channel] = Mix_LoadWAV("Assets/Sounds/ahem_x.wav");
  if (sound == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error sound failed to laod: %s", Mix_GetError());
}

void Audio::PauseMusic(int channel)
{
  Mix_Pause(channel);
};

void Audio::ResumeMusic(int channel)
{
  Mix_Resume(channel);
};
