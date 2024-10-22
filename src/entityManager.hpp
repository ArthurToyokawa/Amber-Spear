#pragma once
#include <SDL2/SDL.h>

#include "list"
#include <systems/auraSystem.hpp>
#include "globals.hpp"

// mudar o nome para world e incuir o mapa
class EntityManager
{
public:
  EntityManager()
  {
    auraSystem = new AuraSystem();
    gStageSystem.loadStage(1);
  };

  void update(float time);
  void handleKeys(std::list<SDL_Keycode> keys);

private:
  AuraSystem *auraSystem;

  // TODO colocar cooldown em jogadores
  int testFbCooldown = 0;

  void makeFireball();
  void removeDeadObjects();
};