#include "gameObjectGenerator.hpp"
#include "textureManager.hpp"
// TODO VER SE É MELHOR SALVAR OS DADOS DE OBJETO DENTRO DO GERADOR
#include "common.hpp"

#include <iostream>

GameObject *GameObjectGenerator::makePlayer(float posX, float posY)
{
  GameObject *go = new GameObject(entityManager, posX, posY);
  go->setSprite("assets/player.png", (int)posX + 0.5, (int)posY + 0.5, 32, 32);
  go->setPhysics(0.0, 0.0, 10, 32, 32, 0);
  return go;
}

GameObject *GameObjectGenerator::makeBox(float posX, float posY)
{
  GameObject *go = new GameObject(entityManager, posX, posY);
  go->setSprite("assets/box.png", (int)posX + 0.5, (int)posY + 0.5, 32, 32);
  go->setPhysics(0.0, 0.0, 10, 32, 32, 0.05);
  return go;
}

GameObject *GameObjectGenerator::makeHeavyBox(float posX, float posY)
{
  GameObject *go = new GameObject(entityManager, posX, posY);
  go->setSprite("assets/BoxHeavy.png", (int)posX + 0.5, (int)posY + 0.5, 32, 32);
  go->setPhysics(0.0, 0.0, 50, 32, 32, 0.1);
  return go;
}

GameObject *GameObjectGenerator::makeFireball(float playerPosX, float playerPosY, float playerAccX, float playerAccY)
{
  int fbStartingX = playerPosX;
  int fbStartingY = playerPosY;
  int fbVelX = 0;
  int fbVelY = 0;
  // setando a direcao da fb baseado na direcao do jogador
  if (playerAccX == 0 && playerAccY == 0)
  {
    fbVelX = FIREBALL_ACCELERATION;
    fbStartingX = playerPosX + 48;
  }
  else
  {
    if (playerAccX > 0)
    {
      fbVelX = FIREBALL_ACCELERATION;
      fbStartingX = playerPosX + 48;
    }
    else if (playerAccX < 0)
    {
      fbVelX = -FIREBALL_ACCELERATION;
      fbStartingX = playerPosX - 48;
    }
    if (playerAccY > 0)
    {
      fbVelY = FIREBALL_ACCELERATION;
      fbStartingY = playerPosY + 48;
    }
    else if (playerAccY < 0)
    {
      fbVelY = -FIREBALL_ACCELERATION;
      fbStartingY = playerPosY - 48;
    }
  }
  // TODO FAZER UM TRATAMENTO PARA EM DIAGONAL A VELIDADE E POSICAO SEREM MENORES
  //  if (fbVelX != 0 && fbVelY != 0)
  //  {
  //    fbVelX = fbVelX / 2;
  //    fbVelY = fbVelY / 2;
  //  }
  //  TODO VER COMO FAZER O JOGADOR NAO COLIDIR COM A PROPRIA SPELL TALVEZ CADA SPELL TEM UM DONO
  //  TALVEZ A SPELL SÓ ATIVA DEPOIS DE UM TIMER
  GameObject *go = new GameObject(entityManager, fbStartingX, fbStartingY);
  go->setSprite("assets/fireball.png", (int)fbStartingX + 0.5, (int)fbStartingY + 0.5, 32, 32);
  go->setPhysics(fbVelX, fbVelY, 0, 32, 32, 0);
  // setting acceleration
  // fb->getPhysics()->setAcceleration(fbVelX, fbVelY);
  go->setSpell(nullptr, FIREBALL_COLISION);
  return go;
}