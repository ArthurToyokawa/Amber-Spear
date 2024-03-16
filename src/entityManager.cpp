
#include "entityManager.hpp"
#include "common.hpp"

EntityManager::EntityManager()
{
  player = new GameObject("assets/player.png", 0, 0, 32, 32);
}

void EntityManager::handleKeys(std::list<SDL_Keycode> keys)
{
  int playerXAcc = 0;
  int playerYAcc = 0;
  for (auto key : keys)
  {
    switch (key)
    {
    case SDLK_UP:
      // player->moveObject(0, -5);
      playerYAcc -= 50;
      break;
    case SDLK_DOWN:
      // player->moveObject(0, +5);
      playerYAcc += 50;
      break;
    case SDLK_LEFT:
      // player->moveObject(-5, 0);
      playerXAcc -= 50;
      break;
    case SDLK_RIGHT:
      // player->moveObject(+5, 0);
      playerXAcc += 50;
      break;
    case SDLK_q:
    {
      // creating fireball
      if (testFbLimiter == 0)
      {
        GameObject *fb = new GameObject("assets/fireball.png", player->getX() + 32, player->getY(), 32, 32);
        fireballs.push_back(fb);
        testFbLimiter = 10;
      }
      break;
    }
    default:
      break;
    }
  }
  player->setAcceleration(playerXAcc, playerYAcc);
}

void EntityManager::update(float time)
{
  // update de fisica
  player->updatePhysics(time);
  for (auto it = fireballs.begin(); it != fireballs.end();)
  {
    auto &fb = *it;
    fb->updatePhysics(time);
    ++it;
  }
  // checa e resolve colisoes
  // TODO
  //  transforma a pos de fisica em uma pos em px
  player->updatePosition();

  // TODO lidando com o comportamento de fireballs, mudar isso para outra classe
  for (auto it = fireballs.begin(); it != fireballs.end();)
  {
    auto &fb = *it;
    // std::cout << fb->getX() << " ";
    fb->moveObject(10, 0);
    if (fb->getX() > SCREEN_WIDTH || fb->getY() > SCREEN_HEIGHT)
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
  if (testFbLimiter != 0)
  {
    testFbLimiter--;
  }
}

void EntityManager::render()
{
  // render objects
  player->render();
  // TODO lidando com o comportamento de fireballs, mudar isso para outra classe
  for (auto &fb : fireballs)
  {
    fb->render();
  }
}