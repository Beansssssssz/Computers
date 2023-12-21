#include <SDL.h>
#include <SDL_mixer.h>

#include "Audio.hpp"


//channel 0 is for backround music/boss fights
//channel 1 is for pop effect(npc or such)
//channel 2 is cause for future 
Audio::Audio(int channels)
{
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, channels, 1024);
  _sound = new Mix_Chunk* [channels];


  if (_sound == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound failed to load: %s", Mix_GetError());

};

Audio* Audio::GetAudioInstance()
{
  if (_audioInstance == NULL)
    _audioInstance = new Audio();

  return _audioInstance;
}

Audio::~Audio()
{
  Mix_CloseAudio();
  delete _sound;
}

void Audio::PlayMusic(int channel, int loop)
{

};

int Audio::GetVolume(int channel)
{
  return Mix_VolumeChunk(_sound[channel], -1);
};

void Audio::SetVolume(int vol, int channel)
{
  Mix_VolumeChunk(_sound[channel], vol);
};

/// <summary>
/// Set the music in the channel to the path
/// </summary>
/// <param name="path">the path to the file of music</param>
/// <param name="channel">the channal number</param>
/// <param name="startPlayin">if to start playing or no,will start
/// in an infinite loop</param>
void Audio::SetMusic(const char* path, int channel, bool startPlayin)
{
  _sound[channel] = Mix_LoadWAV("Assets/Sounds/ahem_x.wav");
  if (_sound == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound failed to load: %s", Mix_GetError());

  if (!startPlayin)
    return;

  if (Mix_PlayChannel(-1, _sound[0], -1))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound failed to play: %s", Mix_GetError());

}

/// <summary>
/// Pauses the music for selected channel or all if no value
/// is recived
/// </summary>
/// <param name="channel"></param>
void Audio::PauseMusic(int channel)
{
  Mix_Pause(channel);
};

/// <summary>
/// Resumes the music for selected channel or all if no value
/// is recived
/// </summary>
/// <param name="channel"></param>
void Audio::ResumeMusic(int channel)
{
  Mix_Resume(channel);
};
