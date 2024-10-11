#pragma once

#include "gameObject.hpp"
#include "textureEnumUtils.hpp"
#include "spriteAnimation.hpp"
#include <vector>
#include "globals.hpp"

class GameObjectGenerator
{
public:
  GameObjectGenerator() {}
  GameObject *makePlayer(float posX, float posY);
  GameObject *makeBox(float posX, float posY);
  GameObject *makeHeavyBox(float posX, float posY);
  GameObject *makeFireball(float playerPosX, float playerPosY, float playerAccX, float playerAccY);
  GameObject *makeRock(float posX, float posY);
  GameObject *makeLava(float posX, float posY);

  SpriteAnimation *makeZeroAnimation();
  std::vector<SpriteAnimation *> makeSingleSpriteAnimations();

private:
  // colisoes
  static void LAVA_COLISION(GameObject *spell, GameObject *target, Vector2f overlap)
  {
    if (target->getLife() != nullptr)
    {
      target->getLife()->dealDamage(10.0f);
    }
    std::cout << "touched lava " << std::endl;
  }
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
    std::cout << "Fireball collision overlap: x: " << overlap.x << " y: " << overlap.y << std::endl;
    std::cout << "Fireball collision effect force: x: " << forceX << " y: " << forceY << std::endl;

    if (target->getPhysics() != nullptr)
    {
      target->getPhysics()->applyForce(forceX, forceY);
    }
    if (target->getLife() != nullptr)
    {
      target->getLife()->dealDamage(10.0f);
    }
    std::cout << "Killing fb " << std::endl;
    // matando spell
    gSoundSystem.playSound(1);
    gPointCounter.addPoints(10);
    spell->kill();
  }
};
