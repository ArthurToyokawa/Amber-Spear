
#include "entityManager.hpp"
#include "common.hpp"
#include "gameObject.hpp"

void EntityManager::loadStartingObjects()
{
  // TODO TODO X.0 MUDAR PARA X.0f para setar como float
  gWorld.getPlayer() = gameObjectGenerator->makePlayer(128.0, 128.0);
  GameObject *box = gameObjectGenerator->makeBox(250.0, 300.0);
  gWorld.getObjects().push_back(box);
  GameObject *hBox = gameObjectGenerator->makeHeavyBox(350.0, 300.0);
  gWorld.getObjects().push_back(hBox);

  // TODO CARREGAR MUSICA BASEADO NO NIVEL
  gSoundSystem.playMusic(0);
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
        gSoundSystem.playSound(0);
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
  // std::cout << "start player anims" << std::endl;
  if (playerXAcc == 0 && playerYAcc == 0) // player parado
  {
    gWorld.getPlayer()->getSprite()->switchToDefaultAnimation();
  }
  else if (playerXAcc == 0) // player se movendo em y
  {
    if (playerYAcc > 0)
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(4); // animDown = 4;
    }
    else
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(3); // animUp = 3;
    }
  }
  else if (playerYAcc == 0) // player de movendo em X
  {
    if (playerXAcc > 0)
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(2); // animRight = 2;
    }
    else
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(1); // animLeft = 1;
    }
  }
  gWorld.getPlayer()->getPhysics()->setAcceleration(playerXAcc, playerYAcc);
  // criando entidades baseado nos clicks do jogador
  if (createFireball)
  {
    gWorld.getPlayer()->getSprite()->switchAnimation(5); // animCasting = 5;
    std::cout << "CREATING FB POS: " << gWorld.getPlayer()->getPosition().x << " " << gWorld.getPlayer()->getPosition().y << " " << playerXAcc << " " << playerYAcc << std::endl;
    GameObject *fb = gameObjectGenerator->makeFireball(gWorld.getPlayer()->getPosition().x, gWorld.getPlayer()->getPosition().y, playerXAcc, playerYAcc);
    gWorld.getSpells().push_back(fb);
    testFbCooldown = 10;
  }
}

void EntityManager::update(float time)
{
  // update de fisica
  gWorld.getPlayer()->updatePhysics(time);
  for (auto it = gWorld.getObjects().begin(); it != gWorld.getObjects().end();)
  {
    auto &obj = *it;
    obj->updatePhysics(time);
    ++it;
  }
  for (auto it = gWorld.getSpells().begin(); it != gWorld.getSpells().end();)
  {
    auto &fb = *it;
    fb->updatePhysics(time);
    ++it;
  }
  // checa e resolve colisoes
  gPhysicsSystem.handleCollisions();
  // remove objetos marcados para remoção (dead)
  removeDeadObjects();

  // transforma a pos de fisica em uma pos em px
  gWorld.getPlayer()->updateSprite();

  // TODO lidando com o comportamento de spells, mudar isso para outra classe
  for (auto it = gWorld.getObjects().begin(); it != gWorld.getObjects().end();)
  {
    auto &obj = *it;
    if (obj->getSprite()->getX() > SCREEN_WIDTH || obj->getSprite()->getY() > SCREEN_HEIGHT)
    {
      delete obj;
      it = gWorld.getObjects().erase(it);
    }
    else
    {
      obj->updateSprite();
      ++it;
    }
  }
  for (auto it = gWorld.getSpells().begin(); it != gWorld.getSpells().end();)
  {
    auto &fb = *it;
    if (fb->getSprite()->getX() > SCREEN_WIDTH || fb->getSprite()->getY() > SCREEN_HEIGHT)
    {
      fb->kill();
      fb->removeChildren();
      delete fb;
      it = gWorld.getSpells().erase(it);
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
  for (auto it = gWorld.getSpells().begin(); it != gWorld.getSpells().end();)
  {
    auto &sp = *it;
    if (sp->isDead())
    {
      std::cout << "removing dead obj" << std::endl;
      sp->removeChildren();
      delete sp;
      it = gWorld.getSpells().erase(it);
    }
    else
    {
      ++it;
    }
  }
  for (auto it = gWorld.getObjects().begin(); it != gWorld.getObjects().end();)
  {
    auto &obj = *it;
    if (obj->isDead())
    {
      std::cout << "removing dead obj" << std::endl;
      obj->removeChildren();
      delete obj;
      it = gWorld.getObjects().erase(it);
    }
    else
    {
      ++it;
    }
  }
}