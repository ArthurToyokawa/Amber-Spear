
#include "entityManager.hpp"
#include "common.hpp"

EntityManager::EntityManager()
{
  player = new GameObject("assets/player.png", 0, 0);
}

void EntityManager::handleKey(SDL_Keycode key)
{
  switch (key)
  {
  case SDLK_UP:
    player->moveObject(0, -5);
    break;
  case SDLK_DOWN:
    player->moveObject(0, +5);
    break;
  case SDLK_LEFT:
    player->moveObject(-5, 0);
    break;
  case SDLK_RIGHT:
    player->moveObject(+5, 0);
    break;
  case SDLK_q:
  {
    // creating fireball
    if (testFbLimiter == 0)
    {
      GameObject *fb = new GameObject("assets/fireball.png", player->getX() + 32, player->getY());
      fireballs.push_back(fb);
      testFbLimiter = 10;
    }
    break;
  }
  default:
    break;
  }
}

void EntityManager::update()
{

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
      fb->update();
      ++it;
    }
  }
  // std::cout << std::endl;
  if (testFbLimiter != 0)
  {
    testFbLimiter--;
  }
  player->update();
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