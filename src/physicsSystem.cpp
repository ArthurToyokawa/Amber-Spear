
#include "physicsSystem.hpp"
#include "common.hpp"

void PhysicsSystem::handleCollisions(GameObject *player, std::list<GameObject *> fireballs, std::list<GameObject *> objects)
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

void PhysicsSystem::resolveSpellCollision(GameObject *spell, GameObject *target)
{
  if (spell->getSpell() != nullptr)
  {
    std::cout << "Killing Spell" << std::endl;
    target->setVelocity(100, 0);
    spell->getSpell()->onCollision();
    spell->kill();
  }
}

void PhysicsSystem::resolveObjectsCollision(GameObject *a, GameObject *b)
{
  float v1x = a->getPhysics()->getVelocity().x;
  float v1y = a->getPhysics()->getVelocity().y;
  float m1 = a->getPhysics()->getMass();
  float v2x = b->getPhysics()->getVelocity().x;
  float v2y = b->getPhysics()->getVelocity().y;
  float m2 = b->getPhysics()->getMass();
  std::cout << "a x: " << v1x << " y: " << v1y << " mass: " << m1 << std::endl;
  std::cout << "b x: " << v2x << " y: " << v2y << " mass: " << m2 << std::endl;
  //  calculando a velocidade apos a colisao
  float v1fx = ((m1 - m2) * v1x + 2 * m2 * v2x) / (m1 + m2);
  float v1fy = ((m1 - m2) * v1y + 2 * m2 * v2y) / (m1 + m2);
  float v2fx = ((m2 - m1) * v2x + 2 * m1 * v1x) / (m1 + m2);
  float v2fy = ((m2 - m1) * v2y + 2 * m1 * v1y) / (m1 + m2);
  // aumentando a forca de retorno para fazer os objetos quicarem com mais forca
  // float v1fx = v1cx + (v1x * -0.1);
  // float v1fy = v1cy + (v1y * -0.1);
  // float v2fx = v2cx + (v2x * -0.1);
  // float v2fy = v2cy + (v2y * -0.1);
  std::cout << "velocidades iniciais a x: " << v1x << " y: " << v1y << std::endl;
  std::cout << "velocidades iniciais b x: " << v2x << " y: " << v2y << std::endl;
  std::cout << "velocidades finais a x: " << v1fx << " y: " << v1fy << std::endl;
  std::cout << "velocidades finais b x: " << v2fx << " y: " << v2fy << std::endl;
  a->setVelocity(v1fx, v1fy);
  b->setVelocity(v2fx, v2fy);
  // movendo os objetos fora de colisao
  teleportObjectsOutOfCollision(a, b);
}

void PhysicsSystem::teleportObjectsOutOfCollision(GameObject *a, GameObject *b)
{
  auto aPos = a->getPhysics()->getPosition();
  auto aSize = a->getPhysics()->getSize();
  auto bPos = b->getPhysics()->getPosition();
  auto bSize = b->getPhysics()->getSize();

  int aLeft = aPos.x;
  int aRight = aPos.x + aSize.x;
  int aTop = aPos.y;
  int aBottom = aPos.y + aSize.y;
  int bLeft = bPos.x;
  int bRight = bPos.x + bSize.x;
  int bTop = bPos.y;
  int bBottom = bPos.y + bSize.y;
  // TODO REVER ESSA LOGICA PARA TELEPORTAR OBJS UM POUCO NA HORIZONTAL E UM POUCO NA VERTICAL
  int overlapX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
  int overlapY = std::min(aBottom, bBottom) - std::max(aTop, bTop);
  std::cout << "overlap x: " << overlapX << " y: " << overlapY << std::endl;

  if (overlapX < overlapY)
  {
    std::cout << "empurrando em x ";
    if (aPos.x < bPos.x)
    {
      std::cout << 'a: ' << aPos.x - overlapX << " b: " << bPos.x + overlapX << std::endl;
      a->getPhysics()->setPosition(aPos.x - overlapX, aPos.y);
      b->getPhysics()->setPosition(bPos.x + overlapX, bPos.y);
    }
    else
    {
      std::cout << 'a: ' << aPos.x + overlapX << " b: " << bPos.x - overlapX << std::endl;
      a->getPhysics()->setPosition(aPos.x + overlapX, aPos.y);
      b->getPhysics()->setPosition(bPos.x - overlapX, bPos.y);
    }
  }
  else
  {
    std::cout << "empurrando em y ";
    if (aPos.y < bPos.y)
    {
      std::cout << 'a: ' << aPos.y - overlapY << " b: " << bPos.y + overlapY << std::endl;
      a->getPhysics()->setPosition(aPos.x, aPos.y - overlapY);
      b->getPhysics()->setPosition(bPos.x, bPos.y + overlapY);
    }
    else
    {
      std::cout << 'a: ' << aPos.y + overlapY << " b: " << bPos.y - overlapY << std::endl;
      a->getPhysics()->setPosition(aPos.x, aPos.y + overlapY);
      b->getPhysics()->setPosition(bPos.x, bPos.y - overlapY);
    }
  }
}

void PhysicsSystem::resolveCollision(GameObject *a, GameObject *b)
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

bool PhysicsSystem::haveObjectsColided(GameObject *a, GameObject *b)
{
  if (a->isDead() || b->isDead())
  {
    std::cout << "Dead object skipping collision check" << std::endl;
    return false;
  }
  auto aPos = a->getPhysics()->getPosition();
  auto aSize = a->getPhysics()->getSize();
  auto bPos = b->getPhysics()->getPosition();
  auto bSize = b->getPhysics()->getSize();
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
