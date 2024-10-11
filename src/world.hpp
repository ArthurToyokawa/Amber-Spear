#pragma once
#include <SDL2/SDL.h>
#include "list"
#include "array"

class GameObject;

class World
{
public:
  World() {};

  GameObject *&getPlayer() { return player; };
  std::list<GameObject *> &getSpells() { return spells; };
  std::list<GameObject *> &getObjects() { return objects; };
  std::array<GameObject *, 500> &getMapObjects() { return mapObjects; };

private:
  GameObject *player;
  std::list<GameObject *> spells;
  std::list<GameObject *> objects;
  std::array<GameObject *, 500> mapObjects;
};
