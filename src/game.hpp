#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

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
  void update();
  void render();
  void clean();

  bool running() { return isRunning; };

  static SDL_Renderer *renderer;

private:
  bool isRunning;
  SDL_Window *window;
};