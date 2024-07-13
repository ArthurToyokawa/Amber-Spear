
#include "entityManager.hpp"
#include "common.hpp"

EntityManager::EntityManager()
{
  player = new GameObject(PLAYER_INFO);
  GameObject *box = new GameObject(BOX_INFO);
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
        std::cout << player->getX() << " " << player->getY() << std::endl;
        GameObject *fb = new GameObject("assets/fireball.png", player->getX() + 32, player->getY(), 32, 32, 0.0);
        // setting acceleration
        fb->setAcceleration(200, 0);
        fb->setSpell(nullptr, FIREBALL_COLISION);
        fireballs.push_back(fb);
        testFbCooldown = 10;
      }
      break;
    }
    default:
      break;
    }
  }
  // se ele estiver andando em apenas uma direcao aumenta sua velocidade
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
  handleCollisions();
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

void EntityManager::handleCollisions() {
  // check for collision with player
  for (auto fireball : fireballs) {
    if (haveObjectsColided(player, fireball)) {
      resolveColision(player, fireball);
      std::cout << "Player and Fireballs have collided." << std::endl;
    }
  }
  for (auto object : objects) {
    if (haveObjectsColided(player, object)) {
      resolveColision(player, object);
      std::cout << "Player and Objects have collided." << std::endl;
    }
  }

  // Check for collisions between fireballs and objects
  for (auto fireball : fireballs) {
    for (auto object : objects) {
      if (haveObjectsColided(fireball, object)) {
        resolveColision(fireball, object);
        std::cout << "Fireballs and Objects have collided." << std::endl;
      }
    }
  }

  // Check for collisions within the fireballs list
  for (auto it1 = fireballs.begin(); it1 != fireballs.end(); ++it1) {
    for (auto it2 = std::next(it1); it2 != fireballs.end(); ++it2) {
      if (haveObjectsColided(*it1, *it2)) {
        resolveColision(*it1, *it2);
        std::cout << "Fireballs have collided." << std::endl;
      }
    }
  }

  // Check for collisions within the objects list
  for (auto it1 = objects.begin(); it1 != objects.end(); ++it1) {
    for (auto it2 = std::next(it1); it2 != objects.end(); ++it2) {
      if (haveObjectsColided(*it1, *it2)) {
        resolveColision(*it1, *it2);
        std::cout << "Objects have collided." << std::endl;
      }
    }
  }
}

void EntityManager::resolveColision(GameObject* a, GameObject* b){
    //TODO chamar o spell resolve collision e dar return
  if(a->getSpell() != nullptr) {
    // Check and delete fireball 'a'
    auto it = std::find(fireballs.begin(), fireballs.end(), a);
    // TODO LOGICA PRA REMOVER A FIREBALL
    // if (it != fireballs.end()) {
    //     it = fireballs.erase(it); // Remove from the list and update iterator
    //     delete *it;          // Delete the object 'a'
    // }
  }
    //TODO resolve de fireball depois enfiar isso em outro metodo separado

  std::cout << "Resolving collision" << std::endl;
}
//TODO VERIFICAR A COLISÃO BASEADO EM PHISYCS
bool EntityManager::haveObjectsColided(GameObject* a, GameObject* b) {
  int obj1Right = a->getX() + a->getWidth();
  int obj1Bottom = a->getY() + a->getHeight();
  int obj2Right = b->getX() + b->getWidth();
  int obj2Bottom = b->getY() + b->getHeight();

  // Check for collision
  if (a->getX() < obj2Right && obj1Right > b->getX() &&
      a->getY() < obj2Bottom && obj1Bottom > b->getY()) {
      return true; 
  }
  return false;
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