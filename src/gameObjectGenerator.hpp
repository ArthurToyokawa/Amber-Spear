#pragma once

#include "gameObject.hpp"
#include "textureEnumUtils.hpp"

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

  static void FIREBALL_COLISION(GameObject *spell, GameObject *target, Vector2f overlap)
  {
    // TODO CRIAR QUANDO CRIAR ANIMACOES USAR UMA ANIMACAO DE EXPLOSAO E NO FINAL EMPURRAR USANDO O CALCULO EM BAIXO
    // // separando a forca em x e y baseado no angulo do overlap
    //  forca em newtons
    // int force = 1000;
    // float totalOverlap = fabs(overlap.x) + fabs(overlap.y);
    // float forceX = force * overlap.x / totalOverlap;
    // float forceY = force * overlap.y / totalOverlap;
    // std::cout << "Fireball collision effect overlap x: " << overlap.x << " y: " << overlap.y
    //           << " total: " << totalOverlap << std::endl;
    // std::cout << "Fireball collision effect force: x: " << forceX << " y: " << forceY << std::endl;

    // calculo da forca baseado em acc
    float forceX = spell->getPhysics()->getVelocity().x * 10;
    float forceY = spell->getPhysics()->getVelocity().y * 10;

    target->getPhysics()->applyForce(forceX, forceY);
    // matando spell
    spell->kill();
  }
};
