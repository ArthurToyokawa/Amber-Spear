#pragma once
#include <SDL2/SDL.h>

#include "list"
#include "gameObject.hpp"

class PhysicsSystem
{
public:
  void handleCollisions(GameObject *player, std::list<GameObject *> fireballs, std::list<GameObject *> objects);
  bool haveObjectsColided(GameObject *a, GameObject *b);
  void resolveCollision(GameObject *a, GameObject *b);
  void resolveSpellCollision(GameObject *a, GameObject *b);
  void resolveObjectsCollision(GameObject *a, GameObject *b);
  void teleportObjectsOutOfCollision(GameObject *a, GameObject *b);
};