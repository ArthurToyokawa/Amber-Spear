#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

class SoundSystem
{
public:
  SoundSystem();
  ~SoundSystem();
  void loadFiles();

  void loadMusic(const char *filename);
  void loadSound(const char *filename);
  void setVolume(int v)
  {
    volume = (MIX_MAX_VOLUME * v) / 100;
  }

  void playMusic(int m);
  void playSound(int s);

  void togglePlay();

private:
  std::vector<Mix_Chunk *> sounds;
  std::vector<Mix_Music *> music;
  int volume;
};