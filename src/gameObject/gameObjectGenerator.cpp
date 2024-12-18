#include <iostream>

#include "gameObjectGenerator.hpp"

#include <common.hpp>
#include <globals.hpp>

#include "gameObject.hpp"
#include "spriteAnimation.hpp"

GameObject *GameObjectGenerator::makePlayer(float posX, float posY)
{
  GameObject *go = new GameObject(posX, posY);
  go->setPhysics(0.0, 0.0, 10, 32, 32, 0, false, false);
  // ANIMATIONS START
  SpriteAnimation *standing = makeZeroAnimation();

  Vector2i posLeft1(32, 32);
  Vector2i posLeft2(64, 32);
  std::vector<Vector2i> positionsLeft = {posLeft1, posLeft2};
  SpriteAnimation *animLeft = new SpriteAnimation(positionsLeft, 0.5f, 0, true);

  Vector2i posRight1(96, 32);
  Vector2i posRight2(0, 64);
  std::vector<Vector2i> positionsRight = {posRight1, posRight2};
  SpriteAnimation *animRight = new SpriteAnimation(positionsRight, 0.5f, 0, true);

  Vector2i posUp1(32, 0);
  Vector2i posUp2(64, 0);
  std::vector<Vector2i> positionsUp = {posUp1, posUp2};
  SpriteAnimation *animUp = new SpriteAnimation(positionsUp, 0.5f, 0, true);

  Vector2i posDown1(96, 0);
  Vector2i posDown2(0, 32);
  std::vector<Vector2i> positionsDown = {posDown1, posDown2};
  SpriteAnimation *animDown = new SpriteAnimation(positionsDown, 0.5f, 0, true);

  Vector2i posCasting1(32, 64);
  std::vector<Vector2i> positionsCasting = {posCasting1};
  SpriteAnimation *animCasting = new SpriteAnimation(positionsCasting, 0.5f, 200, false);
  // standing = 0; animLeft = 1; animRight = 2; animUp = 3; animDown = 4; animCasting = 5;
  std::vector<SpriteAnimation *> animations = {standing, animLeft, animRight, animUp, animDown, animCasting};
  // ANIMATIONS END

  go->setSprite(TextureEnum::player, (int)posX + 0.5, (int)posY + 0.5, 32, 32, animations);
  go->setLife(go, 100.0f, true, 0);

  return go;
}

GameObject *GameObjectGenerator::makeBox(float posX, float posY)
{
  GameObject *go = new GameObject(posX, posY);
  go->setPhysics(0.0, 0.0, 10, 32, 32, 0.05, false, false);
  go->setSprite(TextureEnum::box, (int)posX + 0.5, (int)posY + 0.5, 32, 32, makeSingleSpriteAnimations());
  go->setLife(go, 20.0f, true, 100);
  return go;
}

GameObject *GameObjectGenerator::makeHeavyBox(float posX, float posY)
{
  GameObject *go = new GameObject(posX, posY);
  go->setPhysics(0.0, 0.0, 50, 32, 32, 0.1, false, false);
  go->setSprite(TextureEnum::boxHeavy, (int)posX + 0.5, (int)posY + 0.5, 32, 32, makeSingleSpriteAnimations());
  go->setLife(go, 100.0f, true, 500);
  return go;
}

GameObject *GameObjectGenerator::makeImpassableWall(float posX, float posY, float height, float width)
{
  // TODO USAR UM METODO SEPARADO DE COLISAO
  GameObject *go = new GameObject(posX, posY);
  go->setPhysics(0.0, 0.0, 1000, height, width, 1, false, true);
  return go;
}
GameObject *GameObjectGenerator::makeRock(float posX, float posY)
{
  GameObject *go = new GameObject(posX, posY);
  go->setSprite(TextureEnum::rock, (int)posX + 0.5, (int)posY + 0.5, 32, 32, makeSingleSpriteAnimations());
  return go;
}

GameObject *GameObjectGenerator::makeLava(float posX, float posY)
{
  // TODO USAR UM METODO SEPARADO DE COLISAO
  GameObject *go = new GameObject(posX, posY);
  go->setPhysics(0.0, 0.0, 1000, 32, 32, 1, true, false);
  go->setSprite(TextureEnum::lava, (int)posX + 0.5, (int)posY + 0.5, 32, 32, makeSingleSpriteAnimations());
  go->setSpell(nullptr, LAVA_COLISION);
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
    fbStartingX = playerPosX + 40;
  }
  else
  {
    if (playerAccX > 0)
    {
      fbVelX = FIREBALL_ACCELERATION;
      fbStartingX = playerPosX + 40;
    }
    else if (playerAccX < 0)
    {
      fbVelX = -FIREBALL_ACCELERATION;
      fbStartingX = playerPosX - 40;
    }
    if (playerAccY > 0)
    {
      fbVelY = FIREBALL_ACCELERATION;
      fbStartingY = playerPosY + 40;
    }
    else if (playerAccY < 0)
    {
      fbVelY = -FIREBALL_ACCELERATION;
      fbStartingY = playerPosY - 40;
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
  GameObject *go = new GameObject(fbStartingX, fbStartingY);
  go->setSprite(TextureEnum::fireball, (int)fbStartingX + 0.5, (int)fbStartingY + 0.5, 32, 32, makeSingleSpriteAnimations());
  go->setPhysics(fbVelX, fbVelY, 0, 32, 32, 0, false, false);
  // setting acceleration
  // fb->getPhysics()->setAcceleration(fbVelX, fbVelY);
  go->setSpell(nullptr, FIREBALL_COLISION);
  return go;
}

SpriteAnimation *GameObjectGenerator::makeZeroAnimation()
{
  Vector2i vectZero(0, 0);
  std::vector<Vector2i> posZero = {vectZero};
  SpriteAnimation *zero = new SpriteAnimation(posZero, 1000.0f, 0, true);
  return zero;
}

std::vector<SpriteAnimation *> GameObjectGenerator::makeSingleSpriteAnimations()
{
  std::vector<SpriteAnimation *> singlePos = {makeZeroAnimation()};
  return singlePos;
}

void GameObjectGenerator::LAVA_COLISION(GameObject *spell, GameObject *target, Vector2f overlap)
{
  if (target->getLife() != nullptr)
  {
    target->getLife()->dealDamage(0.2f);
  }
  // std::cout << "touched lava " << std::endl;
}

void GameObjectGenerator::FIREBALL_COLISION(GameObject *spell, GameObject *target, Vector2f overlap)
{
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