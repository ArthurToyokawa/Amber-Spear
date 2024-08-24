#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

class TextureManager;

class Game
{
public:
  // construtor
  Game();
  // deconstrutor
  ~Game();
  // TODO transformar o init em construtor
  void init(const char *tile, int x, int y, int width, int height, bool fullscreen);

  void handleEvents();
  void update(float time);
  void render();
  void clean();
  void gameLoop();

  bool running() { return isRunning; };

private:
  bool isRunning;

  TextureManager *textureManager = nullptr;
};