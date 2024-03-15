#include "game.hpp"
#include "common.hpp"

Game *game = nullptr;

int main(int argc, char *args[])
{
  game = new Game();

  game->init("Amber Spear ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

  return 0;
}