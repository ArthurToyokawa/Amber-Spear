#pragma once
#include <SDL2/SDL.h>

#include "list"
#include "gameObject.hpp"

// mudar o nome para world e incuir o mapa
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
  std::list<GameObject *> objects;
  // TODO rever essa var
  int testFbCooldown = 0;

  void makeFireball();

  void handleCollisions();
  bool haveObjectsColided(GameObject *a, GameObject *b);
  void resolveCollision(GameObject *a, GameObject *b);
  void resolveSpellCollision(GameObject *a, GameObject *b);
  void resolveObjectsCollision(GameObject *a, GameObject *b);
  void removeDeadObjects();
};