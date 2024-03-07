#pragma once
#include "game.hpp"

class GameObject
{

public:
  // TODO setar a pos fora do construtor
  GameObject(const char *textureSheet, int startingX, int startingY);
  ~GameObject();

  void update();
  void render();
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