
#include "entityManager.hpp"
#include "common.hpp"
#include "gameObject.hpp"

void EntityManager::loadStartingObjects()
{
  physicsSystem = new PhysicsSystem(this);
  map = new Map(gameObjectGenerator);
  // TODO TODO X.0 MUDAR PARA X.0f para setar como float
  player = gameObjectGenerator->makePlayer(128.0, 128.0);
  GameObject *box = gameObjectGenerator->makeBox(250.0, 300.0);
  objects.push_back(box);
  GameObject *hBox = gameObjectGenerator->makeHeavyBox(350.0, 300.0);
  objects.push_back(hBox);

  // GameObject *fb = gameObjectGenerator->makeFireball(132.328, 128.348, 100.0, 100.0);
  // spells.push_back(fb);
}
// TODO SEPARAR ESSE TRATAMENTO EM OUTRA CLASSE
void EntityManager::handleKeys(std::list<SDL_Keycode> keys)
{
  // TODO essas var só é necessario em player e tbm inicializa eles fora de funcao
  int playerXAcc = 0;
  int playerYAcc = 0;
  bool createFireball = false;
  for (auto key : keys)
  {
    switch (key)
    {
    case SDLK_UP:
      playerYAcc -= PLAYER_ACCELERATION;
      break;
    case SDLK_DOWN:
      playerYAcc += PLAYER_ACCELERATION;
      break;
    case SDLK_LEFT:
      playerXAcc -= PLAYER_ACCELERATION;
      break;
    case SDLK_RIGHT:
      playerXAcc += PLAYER_ACCELERATION;
      break;
    case SDLK_q:
    {
      // creating fireball
      if (testFbCooldown == 0)
      {
        createFireball = true;
      }
      break;
    }
    default:
      break;
    }
  }
  // se ele estiver andando em apenas uma direcao aumenta sua velocidade
  if (playerXAcc == 0)
  {
    playerYAcc += playerYAcc * 0.5;
  }
  if (playerYAcc == 0)
  {
    playerXAcc += playerXAcc * 0.5;
  }
  // logica para setar a animacao TODO VER SE DA PRA MELHORAR ISSO
  std::cout << "start player anims" << std::endl;
  if (playerXAcc == 0 && playerYAcc == 0) // player parado
  {
    player->getSprite()->switchToDefaultAnimation();
  }
  else if (playerXAcc == 0) // player se movendo em y
  {
    if (playerYAcc > 0)
    {
      player->getSprite()->switchAnimation(4); // animDown = 4;
    }
    else
    {
      player->getSprite()->switchAnimation(3); // animUp = 3;
    }
  }
  else if (playerYAcc == 0) // player de movendo em X
  {
    if (playerXAcc > 0)
    {
      player->getSprite()->switchAnimation(2); // animRight = 2;
    }
    else
    {
      player->getSprite()->switchAnimation(1); // animLeft = 1;
    }
  }
  player->getPhysics()->setAcceleration(playerXAcc, playerYAcc);
  // criando entidades baseado nos clicks do jogador
  if (createFireball)
  {
    player->getSprite()->switchAnimation(5); // animCasting = 5;
    std::cout << "CREATING FB POS: " << player->getPosition().x << " " << player->getPosition().y << " " << playerXAcc << " " << playerYAcc << std::endl;
    GameObject *fb = gameObjectGenerator->makeFireball(player->getPosition().x, player->getPosition().y, playerXAcc, playerYAcc);
    spells.push_back(fb);
    testFbCooldown = 10;
  }
}

void EntityManager::update(float time)
{
  // update de fisica
  player->updatePhysics(time);
  for (auto it = objects.begin(); it != objects.end();)
  {
    auto &obj = *it;
    obj->updatePhysics(time);
    ++it;
  }
  for (auto it = spells.begin(); it != spells.end();)
  {
    auto &fb = *it;
    fb->updatePhysics(time);
    ++it;
  }
  // checa e resolve colisoes
  physicsSystem->handleCollisions();
  // remove objetos marcados para remoção (dead)
  removeDeadObjects();

  // transforma a pos de fisica em uma pos em px
  player->updateSprite();

  // TODO lidando com o comportamento de spells, mudar isso para outra classe
  for (auto it = objects.begin(); it != objects.end();)
  {
    auto &obj = *it;
    if (obj->getSprite()->getX() > SCREEN_WIDTH || obj->getSprite()->getY() > SCREEN_HEIGHT)
    {
      delete obj;
      it = objects.erase(it);
    }
    else
    {
      obj->updateSprite();
      ++it;
    }
  }
  for (auto it = spells.begin(); it != spells.end();)
  {
    auto &fb = *it;
    if (fb->getSprite()->getX() > SCREEN_WIDTH || fb->getSprite()->getY() > SCREEN_HEIGHT)
    {
      delete fb;
      it = spells.erase(it);
    }
    else
    {
      fb->updateSprite();
      ++it;
    }
  }
  // std::cout << std::endl;
  if (testFbCooldown != 0)
  {
    testFbCooldown--;
  }
}

void EntityManager::removeDeadObjects()
{
  for (auto it = spells.begin(); it != spells.end();)
  {
    auto &sp = *it;
    if (sp->isDead())
    {
      std::cout << "removing dead obj" << std::endl;
      sp->removeChildren();
      delete sp;
      it = spells.erase(it);
    }
    else
    {
      ++it;
    }
  }
  for (auto it = objects.begin(); it != objects.end();)
  {
    auto &obj = *it;
    if (obj->isDead())
    {
      std::cout << "removing dead obj" << std::endl;
      obj->removeChildren();
      delete obj;
      it = objects.erase(it);
    }
    else
    {
      ++it;
    }
  }
}