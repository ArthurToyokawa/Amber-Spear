#include "soundSystem.hpp"

SoundSystem::SoundSystem()
{
  Mix_Init(MIX_INIT_MP3);
  SDL_Init(SDL_INIT_AUDIO);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
  }
  setVolume(80);
}

SoundSystem::~SoundSystem()
{
  for (std::vector<Mix_Chunk *>::size_type s = 0; s < sounds.size(); s++)
  {
    Mix_FreeChunk(sounds[s]);
    sounds[s] = NULL;
  }
  for (std::vector<Mix_Chunk *>::size_type s = 0; s < music.size(); s++)
  {
    Mix_FreeMusic(music[s]);
    music[s] = NULL;
  }
  Mix_Quit();
}

void SoundSystem::loadFiles()
{
  loadSound("assets/sounds/magic_cast.wav");
  loadSound("assets/sounds/explosion.wav");
  loadSound("assets/sounds/vine_boom.wav");
  loadMusic("assets/sounds/espionage.mp3");
}

void SoundSystem::loadMusic(const char *filename)
{
  Mix_Music *m = NULL;
  m = Mix_LoadMUS(filename);
  if (m == NULL)
  {
    printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
  }
  music.push_back(m);
}

void SoundSystem::loadSound(const char *filename)
{
  Mix_Chunk *m = NULL;
  m = Mix_LoadWAV(filename);
  if (m == NULL)
  {
    printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
  }
  sounds.push_back(m);
}

void SoundSystem::playMusic(int m)
{
  if (Mix_PlayingMusic() == 0)
  {
    Mix_Volume(1, volume);
    Mix_PlayMusic(music[m], -1);
  }
}
void SoundSystem::playSound(int s)
{
  Mix_Volume(-1, volume);
  Mix_PlayChannel(-1, sounds[s], 0);
}

void SoundSystem::togglePlay()
{
  if (Mix_PausedMusic() == 1)
  {
    Mix_ResumeMusic();
  }
  else
  {
    Mix_PauseMusic();
  }
}