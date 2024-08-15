#pragma once

#include "gameObject.hpp"

class EntityManager;

class GameObjectGenerator
{
public:
  GameObjectGenerator(EntityManager *e)
  {
    entityManager = e;
  }
  GameObject *makePlayer(float posX, float posY);
  GameObject *makeBox(float posX, float posY);
  GameObject *makeHeavyBox(float posX, float posY);
  GameObject *makeFireball(float playerPosX, float playerPosY, float playerAccX, float playerAccY);

private:
  EntityManager *entityManager = nullptr;
};
