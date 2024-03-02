#pragma once
#include "game.hpp"

class GameObject
{

public:
  GameObject(const char *textureSheet, int startingX, int startingY);
  ~GameObject();

  void update();
  void render();

private:
  int xpos;
  int ypos;

  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;
};