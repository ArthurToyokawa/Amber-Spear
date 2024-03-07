#include "game.hpp"

Game *game = nullptr;

int main(int argc, char *args[])
{
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  game = new Game();

  game->init("Amber Spear ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
  // TODO colocar o loop em game
  //  TODO converter em secs para lidar com fisica
  frameTime = 0;
  while (game->running())
  {

    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay >= frameTime)
    {
      SDL_Delay(frameDelay - frameTime);
    }
    else
    {
      /*TODO TRATAR LAG */
    }
    frameTime = SDL_GetTicks() - frameStart;
  }

  game->clean();

  return 0;
}