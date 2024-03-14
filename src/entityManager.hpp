#pragma once
#include <SDL2/SDL.h>

#include "list"
#include "gameObject.hpp"

class EntityManager
{

public:
  EntityManager();
  void update();
  void render();
  void handleKey(SDL_Keycode key);

private:
  GameObject *player;
  std::list<GameObject *> fireballs;
  // TODO rever essa var
  int testFbLimiter = 0;

  void makeFireball();
};