#pragma once
#include <SDL2/SDL.h>

#include "list"
#include <gameObject/gameObjectGenerator.hpp>
#include <systems/mapManager.hpp>
#include "globals.hpp"

// mudar o nome para world e incuir o mapa
class EntityManager
{
public:
  EntityManager(GameObjectGenerator *g)
  {
    gameObjectGenerator = g;
    loadStartingObjects();
  };
  void loadStartingObjects();

  void update(float time);
  void handleKeys(std::list<SDL_Keycode> keys);

private:
  GameObjectGenerator *gameObjectGenerator;
  // TODO rever essa var
  int testFbCooldown = 0;

  void makeFireball();
  void removeDeadObjects();
};