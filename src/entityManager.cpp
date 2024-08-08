
#include "entityManager.hpp"
#include "common.hpp"

EntityManager::EntityManager()
{
  player = new GameObject(PLAYER_INFO);
  GameObject *box = new GameObject(BOX_INFO);
  objects.push_back(box);
  GameObject *hBox = new GameObject(HEAVY_BOX_INFO);
  objects.push_back(hBox);
}

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
  player->getPhysics()->setAcceleration(playerXAcc, playerYAcc);
  // criando entidades baseado nos clicks do jogador
  if (createFireball)
  {
    // TODO USAR O POS DE GAMEOBJECT EM TODO getSprite()->get
    std::cout << player->getSprite()->getX() << " " << player->getSprite()->getY() << std::endl;

    // setando a direcao da fb baseado na direcao do jogador
    int fbXAcc = 0;
    int fbYAcc = 0;
    int fbStartingX = player->getSprite()->getX();
    int fbStartingY = player->getSprite()->getY();
    if (playerXAcc == 0 && playerYAcc == 0)
    {
      fbXAcc = FIREBALL_ACCELERATION;
      fbStartingX = player->getSprite()->getX() + 48;
    }
    else
    {
      if (playerXAcc > 0)
      {
        fbXAcc = FIREBALL_ACCELERATION;
        fbStartingX = player->getSprite()->getX() + 48;
      }
      else if (playerXAcc < 0)
      {
        fbXAcc = -FIREBALL_ACCELERATION;
        fbStartingX = player->getSprite()->getX() - 48;
      }
      if (playerYAcc > 0)
      {
        fbYAcc = FIREBALL_ACCELERATION;
        fbStartingY = player->getSprite()->getY() + 48;
      }
      else if (playerYAcc < 0)
      {
        fbYAcc = -FIREBALL_ACCELERATION;
        fbStartingY = player->getSprite()->getY() - 48;
      }
    }
    GameObject *fb = new GameObject("assets/fireball.png", fbStartingX, fbStartingY, 32, 32, 0.0);
    // setting acceleration
    // TODO VER COMO FAZER O JOGADOR NAO COLIDIR COM A PROPRIA SPELL TALVEZ CADA SPELL TEM UM DONO
    fb->getPhysics()->setVelocity(player->getPhysics()->getVelocity().x, player->getPhysics()->getVelocity().y);
    fb->setSpell(nullptr, FIREBALL_COLISION);
    fb->getPhysics()->setAcceleration(fbXAcc, fbYAcc);

    fireballs.push_back(fb);
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
  for (auto it = fireballs.begin(); it != fireballs.end();)
  {
    auto &fb = *it;
    fb->updatePhysics(time);
    ++it;
  }
  // checa e resolve colisoes
  physicsSystem.handleCollisions(player, fireballs, objects);
  // remove objetos marcados para remoção (dead)
  removeDeadObjects();
  // transforma a pos de fisica em uma pos em px
  player->updatePosition();

  // TODO lidando com o comportamento de fireballs, mudar isso para outra classe
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
      obj->updatePosition();
      ++it;
    }
  }
  for (auto it = fireballs.begin(); it != fireballs.end();)
  {
    auto &fb = *it;
    if (fb->getSprite()->getX() > SCREEN_WIDTH || fb->getSprite()->getY() > SCREEN_HEIGHT)
    {
      delete fb;
      it = fireballs.erase(it);
    }
    else
    {
      fb->updatePosition();
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
  for (auto it = fireballs.begin(); it != fireballs.end();)
  {
    auto &fb = *it;
    if (fb->isDead())
    {
      delete fb;
      it = fireballs.erase(it);
    }
    else
    {
      ++it;
    }
  }
  // TODO handle objects dying
}

void EntityManager::render()
{
  // render objects
  player->getSprite()->render();
  for (auto &objs : objects)
  {
    objs->getSprite()->render();
  }
  for (auto &fb : fireballs)
  {
    fb->getSprite()->render();
  }
}