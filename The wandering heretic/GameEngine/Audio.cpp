#include <SDL.h>
#include <SDL_mixer.h>

#include "Audio.hpp"


//channel 0 is for backround music/boss fights
//channel 1 is for pop effect(npc or such)
Audio::Audio()
{
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, CHANNELS_COUNT, 1024);
  _sound = new Mix_Chunk* [CHANNELS_COUNT];
  _paused = new bool(CHANNELS_COUNT);

  StartMusic();
  SetVolume(MAX_VAL / 2, 0);
};

/// <summary>
/// returns the instance to the static object of this class
/// this is the only way to get an object of this class
/// this always returns the same object
/// </summary>
/// <returns></returns>
Audio* Audio::GetAudioInstance()
{
  if (_audioInstance == nullptr)
    _audioInstance = new Audio();

  return _audioInstance;
}

Audio::~Audio()
{
  Mix_CloseAudio();
  delete _sound[0];
  if (_sound[1] != nullptr)
    delete _sound[1];

  delete _sound;
}

/// <summary>
/// starts all the music
/// </summary>
void Audio::StartMusic()
{
  _sound[0] = Mix_LoadWAV("Assets/Sounds/MainMusic.mp3");
  if(_sound[0] == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound failed to load: %s", Mix_GetError());

  if(Mix_PlayChannel(0, _sound[0], -1) == -1)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound could not be played: %s", Mix_GetError());
};

/// <summary>
/// returns the volume of the channel,if var is left empty or -1
/// then returns
/// </summary>
/// <param name="channel"></param>
/// <returns></returns>
int Audio::GetVolume(int channel)
{
  return Mix_VolumeChunk(_sound[channel], -1);
};

/// <summary>
/// sets the volume to the value recived.
/// if the channel parameter is empty all channels are effected
/// </summary>
/// <param name="vol">the volume</param>
/// <param name="channel">the channel
/// leave empty or enter as -1 for every channel</param>
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
void Audio::SetMusic(const char* path, int channel, int loops, bool startPlayin)
{
  _sound[channel] = Mix_LoadWAV(path);
  if (_sound == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound failed to load: %s", Mix_GetError());

  if (!startPlayin)
    return;

  if (Mix_PlayChannel(channel, _sound[channel], loops))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
      "Error _sound failed to play: %s", Mix_GetError());

}

/// <summary>
/// sets the music the the boolean value recived
/// if true them music isnt paused
/// otherwise music is paused
/// </summary>
/// <param name="state"></param>
/// <param name="channel"></param>
void Audio::SetMusicState(bool state, int channel) {
  if (state)
    PauseMusic(channel);
  else
    ResumeMusic(channel);
}

/// <summary>
/// Pauses the music for selected channel or all if no value
/// is recived
/// </summary>
/// <param name="channel"></param>
void Audio::PauseMusic(int channel)
{
  if (channel >= 0)
    _paused[channel] = true;
  else
    for (char i = 0; i < CHANNELS_COUNT; i++)
      _paused[channel] = true;

  Mix_Pause(channel);
};

/// <summary>
/// Resumes the music for selected channel or all if no value
/// is recived
/// </summary>
/// <param name="channel"></param>
void Audio::ResumeMusic(int channel)
{
  if (channel >= 0)
    _paused[channel] = false;
  else
    for (char i = 0; i < CHANNELS_COUNT; i++)
      _paused[channel] = false;

  Mix_Resume(channel);
};
