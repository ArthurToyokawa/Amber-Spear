// tratando de erros caso multiplos imports desse header
#ifndef Game_hpp
#define Game_hpp

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

  void init(const char *tile, int x, int y, int width, int height, bool fullscreen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running() { return isRunning; };

private:
  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;
  int counterX = 0;
  int counterY = 0;
  bool vertical = true;
  bool horizontal = true;
};

#endif /* Game_hpp */