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
    gStageSystem.loadStage(2);
  };

  void update(float time);
  void handleKeys(std::list<SDL_Keycode> keys);
  void handleKeysP2(std::list<SDL_Keycode> keys);

private:
  AuraSystem *auraSystem;

  // TODO colocar cooldown em jogadores
  int fbCooldown = 0;
  int fbCooldown2 = 0;
  int massAuraCooldown = 0;
  int massAuraCooldown2 = 0;

  void makeFireball();
  void removeDeadObjects();
};