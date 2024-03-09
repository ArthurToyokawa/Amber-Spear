#pragma once
#include "game.hpp"

class GameObject
{

public:
  // TODO setar a pos fora do construtor
  GameObject(const char *textureSheet, int startingX, int startingY);

  void update();
  void render();
  int getX()
  {
    return xpos;
  }
  int getY()
  {
    return ypos;
  }
  void moveObject(int x, int y)
  {
    xpos = xpos + x;
    ypos = ypos + y;
  }
  // utilizar gameObject como superclasse para entidades
  // virtual void update() = 0;
  // virtual void render() = 0;

private:
  // TODO posicao em vetor
  int xpos;
  int ypos;

  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;
};