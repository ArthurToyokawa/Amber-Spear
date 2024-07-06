
#include "entityManager.hpp"
#include "common.hpp"

EntityManager::EntityManager()
{
  player = new GameObject("assets/player.png", 128, 128, 32, 32, 0.0);
  GameObject *box = new GameObject("assets/box.png", 300, 300, 32, 32, 0.1);
  objects.push_back(box);
  }

void EntityManager::handleKeys(std::list<SDL_Keycode> keys)
{
  // TODO essas var só é necessario em player e tbm inicializa eles fora de funcao
  int playerXAcc = 0;
  int playerYAcc = 0;
  for (auto key : keys)
  {
    switch (key)
    {
    case SDLK_UP:
      playerYAcc -= 100;
      break;
    case SDLK_DOWN:
      playerYAcc += 100;
      break;
    case SDLK_LEFT:
      playerXAcc -= 100;
      break;
    case SDLK_RIGHT:
      playerXAcc += 100;
      break;
    case SDLK_q:
    {
      // creating fireball
      if (testFbCooldown == 0)
      {
        std::cout << player->getX() << " " << player->getY() << std::endl;
        GameObject *fb = new GameObject("assets/fireball.png", player->getX() + 32, player->getY(), 32, 32, 0.0);
        // setting acceleration
        fb->setAcceleration(200, 0);
        fireballs.push_back(fb);
        testFbCooldown = 10;
      }
      break;
    }
    default:
      break;
    }
  }
  // se ele estiver andando em apenas uma diracao aumenta sua velocidade
  if(playerXAcc == 0) {
    playerYAcc += playerYAcc*0.5;
  }
  if(playerYAcc == 0) {
    playerXAcc += playerXAcc*0.5;
  }
  player->setAcceleration(playerXAcc, playerYAcc);
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
  // TODO
  //  transforma a pos de fisica em uma pos em px
  player->updatePosition();

  // TODO lidando com o comportamento de fireballs, mudar isso para outra classe
  for (auto it = objects.begin(); it != objects.end();)
  {
    auto &obj = *it;
    if (obj->getX() > SCREEN_WIDTH || obj->getY() > SCREEN_HEIGHT)
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
  if (testFbCooldown != 0)
  {
    testFbCooldown--;
  }
}


  bool haveObjectsColided(GameObject a, GameObject b){
    if (r1->x + r1->width/2 < r2->x - r2->width/2) return 0;
    if (r1->x - r1->width/2 > r2->x + r2->width/2) return 0;
    if (r1->y + r1->height/2 < r2->y - r2->height/2) return 0;
    if (r1->y - r1->height/2 > r2->y + r2->height/2) return 0;
    return 1;
  }

  void resolveColision(){

  }

void EntityManager::render()
{
  // render objects
  player->render();
  for (auto &objs : objects)
  {
    objs->render();
  }
  for (auto &fb : fireballs)
  {
    fb->render();
  }
}