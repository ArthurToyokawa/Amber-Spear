
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
  player->setAcceleration(playerXAcc, playerYAcc);
  // criando entidades baseado nos clicks do jogador
  if (createFireball)
  {
    std::cout << player->getX() << " " << player->getY() << std::endl;

    // setando a direcao da fb baseado na direcao do jogador
    int fbXAcc = 0;
    int fbYAcc = 0;
    int fbStartingX = player->getX();
    int fbStartingY = player->getY();
    if (playerXAcc == 0 && playerYAcc == 0)
    {
      fbXAcc = FIREBALL_ACCELERATION;
      fbStartingX = player->getX() + 48;
    }
    else
    {
      if (playerXAcc > 0)
      {
        fbXAcc = FIREBALL_ACCELERATION;
        fbStartingX = player->getX() + 48;
      }
      else if (playerXAcc < 0)
      {
        fbXAcc = -FIREBALL_ACCELERATION;
        fbStartingX = player->getX() - 48;
      }
      if (playerYAcc > 0)
      {
        fbYAcc = FIREBALL_ACCELERATION;
        fbStartingY = player->getY() + 48;
      }
      else if (playerYAcc < 0)
      {
        fbYAcc = -FIREBALL_ACCELERATION;
        fbStartingY = player->getY() - 48;
      }
    }
    GameObject *fb = new GameObject("assets/fireball.png", fbStartingX, fbStartingY, 32, 32, 0.0);
    // setting acceleration
    // TODO VER SE E MELHOR TER TODOS ESSES METODOS DIRETO EM GAMEOBJECT AO INVES DE player->getPhysics().getVelocity()
    // TODO VER COMO FAZER O JOGADOR NAO COLIDIR COM A PROPRIA SPELL TALVEZ CADA SPELL TEM UM DONO
    fb->setVelocity(player->getPhysics().getVelocity().x, player->getPhysics().getVelocity().y);
    fb->setSpell(nullptr, FIREBALL_COLISION);
    fb->setAcceleration(fbXAcc, fbYAcc);

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
  handleCollisions();
  // remove objetos marcados para remoção (dead)
  removeDeadObjects();
  // transforma a pos de fisica em uma pos em px
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

void EntityManager::handleCollisions()
{
  // check for collision with player
  for (auto fireball : fireballs)
  {
    if (haveObjectsColided(player, fireball))
    {
      std::cout << "Player and Fireballs have collided." << std::endl;
      resolveCollision(player, fireball);
    }
  }
  for (auto object : objects)
  {
    if (haveObjectsColided(player, object))
    {
      std::cout << "Player and Objects have collided." << std::endl;
      resolveCollision(player, object);
    }
  }

  // Check for collisions between fireballs and objects
  for (auto fireball : fireballs)
  {
    for (auto object : objects)
    {
      if (haveObjectsColided(fireball, object))
      {
        std::cout << "Fireballs and Objects have collided." << std::endl;
        resolveCollision(fireball, object);
      }
    }
  }

  // Check for collisions within the fireballs list
  for (auto it1 = fireballs.begin(); it1 != fireballs.end(); ++it1)
  {
    for (auto it2 = std::next(it1); it2 != fireballs.end(); ++it2)
    {
      if (haveObjectsColided(*it1, *it2))
      {
        std::cout << "Fireballs have collided." << std::endl;
        resolveCollision(*it1, *it2);
      }
    }
  }

  // Check for collisions within the objects list
  for (auto it1 = objects.begin(); it1 != objects.end(); ++it1)
  {
    for (auto it2 = std::next(it1); it2 != objects.end(); ++it2)
    {
      if (haveObjectsColided(*it1, *it2))
      {
        std::cout << "Objects have collided." << std::endl;
        resolveCollision(*it1, *it2);
      }
    }
  }
}

void EntityManager::resolveSpellCollision(GameObject *spellCaster, GameObject *target)
{
  if (spellCaster->getSpell() != nullptr)
  {
    std::cout << "Killing Spell" << std::endl;
    target->setVelocity(100, 0);
    spellCaster->getSpell()->onCollision();
    spellCaster->kill();
  }
}

void EntityManager::resolveObjectsCollision(GameObject *a, GameObject *b)
{
  float v1x = a->getPhysics().getVelocity().x;
  float v1y = a->getPhysics().getVelocity().y;
  float m1 = a->getPhysics().getMass();
  float v2x = b->getPhysics().getVelocity().x;
  float v2y = b->getPhysics().getVelocity().y;
  float m2 = b->getPhysics().getMass();
  std::cout << "a x: " << v1x << " y: " << v1y << " mass: " << m1 << std::endl;
  std::cout << "b x: " << v2x << " y: " << v2y << " mass: " << m2 << std::endl;
  // calculando a velocidade apos a colisao
  float v1cx = ((m1 - m2) * v1x + 2 * m2 * v2x) / (m1 + m2);
  float v1cy = ((m1 - m2) * v1y + 2 * m2 * v2y) / (m1 + m2);
  float v2cx = ((m2 - m1) * v2x + 2 * m1 * v1x) / (m1 + m2);
  float v2cy = ((m2 - m1) * v2y + 2 * m1 * v1y) / (m1 + m2);
  // aumentando a forca de retorno para fazer os objetos quicarem com mais forca
  float v1fx = v1cx + (v2cx * -0.1);
  float v1fy = v1cy + (v2cy * -0.1);
  float v2fx = v2cx + (v1cx * -0.1);
  float v2fy = v2cy + (v1cy * -0.1);
  std::cout << "velocidades finais a x: " << v1fx << " y: " << v1fy << std::endl;
  std::cout << "velocidades finais b x: " << v2fx << " y: " << v2fy << std::endl;
  a->setVelocity(v1fx, v1fy);
  b->setVelocity(v2fx, v2fy);
}

void EntityManager::resolveCollision(GameObject *a, GameObject *b)
{
  std::cout << "Resolving collision" << std::endl;
  if (a->getSpell() == nullptr && b->getSpell() == nullptr)
  {
    std::cout << "Neither object is a spell" << std::endl;
    resolveObjectsCollision(a, b);
  }
  else
  {
    resolveSpellCollision(a, b);
    resolveSpellCollision(b, a);
  }
}
// TODO VERIFICAR A COLISÃO BASEADO EM PHISYCS
bool EntityManager::haveObjectsColided(GameObject *a, GameObject *b)
{
  if (a->isDead() || b->isDead())
  {
    std::cout << "Dead object skipping collision check" << std::endl;
    return false;
  }
  auto aPos = a->getPhysics().getPosition();
  auto aSize = a->getPhysics().getSize();
  auto bPos = b->getPhysics().getPosition();
  auto bSize = b->getPhysics().getSize();
  // std::cout << "a pos x:" << aPos.x << " y:" << aPos.y << " a size x:" << aSize.x << " y:" << aSize.y << std::endl;
  // std::cout << "b pos x:" << bPos.x << " y:" << bPos.y << " b size x:" << aSize.x << " y:" << aSize.y << std::endl;
  int aLeft = aPos.x;
  int aRight = aPos.x + aSize.x;
  int aTop = aPos.y;
  int aBottom = aPos.y + aSize.y;
  int bLeft = bPos.x;
  int bRight = bPos.x + bSize.x;
  int bTop = bPos.y;
  int bBottom = bPos.y + bSize.y;

  // Check for collision
  if (aLeft < bRight && aRight > bLeft &&
      aTop < bBottom && aBottom > bTop)
  {
    return true;
  }
  return false;
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