#pragma once
#include <SDL2/SDL.h>

#include "list"
#include "gameObject.hpp"
#include "physicsSystem.hpp"
#include "gameObjectGenerator.hpp"

// mudar o nome para world e incuir o mapa
class EntityManager
{
public:
  EntityManager();
  void update(float time);
  void render();
  void handleKeys(std::list<SDL_Keycode> keys);

private:
  // objetos
  GameObject *player;
  std::list<GameObject *> fireballs;
  std::list<GameObject *> objects;
  GameObjectGenerator gameObjectGenerator;
  // sistemas
  PhysicsSystem physicsSystem;
  // TODO rever essa var
  int testFbCooldown = 0;

  void makeFireball();
  void removeDeadObjects();
};