#pragma once

#include "gameObject.hpp"

class GameObjectGenerator
{
public:
  GameObject *makePlayer(float posX, float posY);
  GameObject *makeBox(float posX, float posY);
  GameObject *makeHeavyBox(float posX, float posY);
  GameObject *makeFireball(float playerPosX, float playerPosY, float playerAccX, float playerAccY);

private:
};
