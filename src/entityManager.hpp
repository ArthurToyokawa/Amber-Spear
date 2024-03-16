#pragma once
#include <SDL2/SDL.h>

#include "list"
#include "gameObject.hpp"

class EntityManager
{

public:
  EntityManager();
  void update(float time);
  void render();
  void handleKeys(std::list<SDL_Keycode> keys);

private:
  GameObject *player;
  std::list<GameObject *> fireballs;
  // TODO rever essa var
  int testFbLimiter = 0;

  void makeFireball();
};