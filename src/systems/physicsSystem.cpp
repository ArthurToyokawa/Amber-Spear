
#include "physicsSystem.hpp"
#include <gameObject/gameObject.hpp>
#include <common.hpp>

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::handleCollisions()
{
  GameObject *&player = gWorld.getPlayer();
  GameObject *&player2 = gWorld.getPlayer2();
  std::list<GameObject *> &spells = gWorld.getSpells();
  std::list<GameObject *> &objects = gWorld.getObjects();
  std::array<GameObject *, 500> &mapObjects = gWorld.getMapObjects();
  if (gWorld.hasPlayer2())
  {
    ObjectsCollision col = haveObjectsCollided(player, player2);
    if (col.haveCollided)
    {
      std::cout << "Players have collided." << std::endl;
      resolveCollision(player, player2, col.overlap);
    }
  }
  // check for collision with player
  for (auto spell : spells)
  {
    ObjectsCollision col = haveObjectsCollided(player, spell);
    if (col.haveCollided)
    {
      std::cout << "Player and Spells have collided." << std::endl;
      resolveCollision(player, spell, col.overlap);
    }
    if (gWorld.hasPlayer2())
    {
      ObjectsCollision col2 = haveObjectsCollided(player2, spell);
      if (col2.haveCollided)
      {
        resolveCollision(player2, spell, col2.overlap);
      }
    }
  }
  for (auto object : objects)
  {
    ObjectsCollision col = haveObjectsCollided(player, object);
    if (col.haveCollided)
    {
      std::cout << "Player and Objects have collided." << std::endl;
      resolveCollision(player, object, col.overlap);
    }
    if (gWorld.hasPlayer2())
    {
      ObjectsCollision col2 = haveObjectsCollided(player2, object);
      if (col2.haveCollided)
      {
        resolveCollision(player2, object, col2.overlap);
      }
    }
  }
  for (auto tile : mapObjects)
  {
    ObjectsCollision col = haveObjectsCollided(player, tile);
    if (col.haveCollided)
    {
      resolveCollision(player, tile, col.overlap);
    }
    if (gWorld.hasPlayer2())
    {
      ObjectsCollision col2 = haveObjectsCollided(player2, tile);
      if (col2.haveCollided)
      {
        resolveCollision(player2, tile, col2.overlap);
      }
    }
  }

  // Check for collisions between spells and objects
  for (auto spell : spells)
  {
    for (auto object : objects)
    {
      ObjectsCollision col = haveObjectsCollided(spell, object);
      if (col.haveCollided)
      {
        std::cout << "Spells and Objects have collided." << std::endl;
        resolveCollision(spell, object, col.overlap);
      }
    }
  }

  // Check for collisions within the spells list
  for (auto it1 = spells.begin(); it1 != spells.end(); ++it1)
  {
    for (auto it2 = std::next(it1); it2 != spells.end(); ++it2)
    {
      ObjectsCollision col = haveObjectsCollided(*it1, *it2);
      if (col.haveCollided)
      {
        std::cout << "Spells have collided." << std::endl;
        resolveCollision(*it1, *it2, col.overlap);
      }
    }
  }

  // Check for collisions between objects and mapTiles
  for (auto object : objects)
  {
    for (auto tile : mapObjects)
    {
      ObjectsCollision col = haveObjectsCollided(object, tile);
      if (col.haveCollided)
      {
        resolveCollision(object, tile, col.overlap);
      }
    }
  }
  // Check for collisions within the objects list
  for (auto it1 = objects.begin(); it1 != objects.end(); ++it1)
  {
    for (auto it2 = std::next(it1); it2 != objects.end(); ++it2)
    {
      ObjectsCollision col = haveObjectsCollided(*it1, *it2);
      if (col.haveCollided)
      {
        std::cout << "Objects have collided." << std::endl;
        resolveCollision(*it1, *it2, col.overlap);
      }
    }
  }
}
ObjectsCollision PhysicsSystem::haveObjectsCollided(GameObject *a, GameObject *b)
{
  if (
      a->isDead() ||
      b->isDead() ||
      a->getPhysics() == nullptr ||
      b->getPhysics() == nullptr)
  {
    // std::cout << "Skipping collision check" << std::endl;
    Vector2f overlap;
    overlap.set(0, 0);
    return {
        false,
        overlap};
  }
  Vector2f overlap = getCollisionOverlap(a, b);
  bool haveCollided = overlap.x != 0 && overlap.y != 0;
  return {
      haveCollided,
      overlap};
}

Vector2f PhysicsSystem::getCollisionOverlap(GameObject *a, GameObject *b)
{
  Vector2f aPos = a->getPosition();
  Vector2f aSize = a->getPhysics()->getSize();
  Vector2f bPos = b->getPosition();
  Vector2f bSize = b->getPhysics()->getSize();
  int aLeft = aPos.x;
  int aRight = aPos.x + aSize.x;
  int aTop = aPos.y;
  int aBottom = aPos.y + aSize.y;
  int bLeft = bPos.x;
  int bRight = bPos.x + bSize.x;
  int bTop = bPos.y;
  int bBottom = bPos.y + bSize.y;

  Vector2f overlapVector;
  overlapVector.set(0, 0);
  // Check for collision
  if ((aLeft < bRight && aRight > bLeft))
  {
    if (aLeft < bLeft)
    {
      overlapVector.x = aRight - bLeft;
      // std::cout << "colliding from right " << overlapVector.x << std::endl;
    }
    else
    {
      overlapVector.x = aLeft - bRight;
      // std::cout << "colliding from left " << overlapVector.x << std::endl;
    }
  }
  if (aTop < bBottom && aBottom > bTop)
  {
    if (aTop < bTop)
    {
      overlapVector.y = (bTop - aBottom) * -1.0;
      // std::cout << "colliding from top " << overlapVector.y << std::endl;
    }
    else
    {
      overlapVector.y = (bBottom - aTop) * -1.0;
      // std::cout << "colliding from bottom " << overlapVector.y << std::endl;
    }
  }
  return overlapVector;
}

void PhysicsSystem::resolveImmovableObjectCollision(GameObject *a, GameObject *b, Vector2f overlap)
{
  std::cout << "colliding with impassable object " << std::endl;
  if (a->getPhysics()->getIsUnstoppable() && b->getPhysics()->getIsUnstoppable())
  {
    return;
  }
  else if (a->getPhysics()->getIsUnstoppable())
  {
    b->getPhysics()->setVelocity(b->getPhysics()->getVelocity().x * -0.5, b->getPhysics()->getVelocity().y * -0.5);
    b->getPhysics()->setAcceleration(b->getPhysics()->getAcceleration().x * -0.5, b->getPhysics()->getAcceleration().y * -0.5);
    teleportOneObjectOutOfCollision(a, b, overlap);
  }
  else
  {
    a->getPhysics()->setVelocity(a->getPhysics()->getVelocity().x * -0.5, a->getPhysics()->getVelocity().y * -0.5);
    a->getPhysics()->setAcceleration(a->getPhysics()->getAcceleration().x * -0.5, a->getPhysics()->getAcceleration().y * -0.5);
    teleportOneObjectOutOfCollision(b, a, overlap);
  }
}
void PhysicsSystem::teleportOneObjectOutOfCollision(GameObject *standing, GameObject *moving, Vector2f overlap)
{
  // teleportando o a para fora de b
  if (fabsf(overlap.x) < fabsf(overlap.y))
  {
    std::cout << "empurrando em x " << overlap.x << std::endl;
    if (overlap.x > 0)
    {
      moving->setPosition(standing->getPosition().x - moving->getPhysics()->getSize().x - 1.0, moving->getPosition().y);
    }
    else
    {
      moving->setPosition(standing->getPosition().x + standing->getPhysics()->getSize().x + 1.0, moving->getPosition().y);
    }
  }
  else
  {
    std::cout << "empurrando em y " << overlap.y << std::endl;
    if (overlap.y > 0)
    {
      std::cout << "TEST " << standing->getPosition().y << std::endl;
      moving->setPosition(moving->getPosition().x, standing->getPosition().y - moving->getPhysics()->getSize().y - 1.0);
    }
    else
    {
      moving->setPosition(moving->getPosition().x, standing->getPosition().y + standing->getPhysics()->getSize().y + 1.0);
    }
  }
}

void PhysicsSystem::resolveObjectsCollision(GameObject *a, GameObject *b, Vector2f overlap)
{
  float v1x = a->getPhysics()->getVelocity().x;
  float v1y = a->getPhysics()->getVelocity().y;
  float m1 = a->getPhysics()->getMass();
  float v2x = b->getPhysics()->getVelocity().x;
  float v2y = b->getPhysics()->getVelocity().y;
  float m2 = b->getPhysics()->getMass();
  // std::cout << "a x: " << v1x << " y: " << v1y << " mass: " << m1 << std::endl;
  // std::cout << "b x: " << v2x << " y: " << v2y << " mass: " << m2 << std::endl;
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
  // std::cout << "velocidades iniciais a x: " << v1x << " y: " << v1y << std::endl;
  // std::cout << "velocidades iniciais b x: " << v2x << " y: " << v2y << std::endl;
  // std::cout << "velocidades finais a x: " << v1fx << " y: " << v1fy << std::endl;
  // std::cout << "velocidades finais b x: " << v2fx << " y: " << v2fy << std::endl;
  a->getPhysics()->setVelocity(v1fx, v1fy);
  b->getPhysics()->setVelocity(v2fx, v2fy);
  // movendo os objetos fora de colisao
  teleportObjectsOutOfCollision(a, b, overlap);
}

void PhysicsSystem::teleportObjectsOutOfCollision(GameObject *a, GameObject *b, Vector2f overlap)
{
  // teleportando o a para fora de b
  if (fabsf(overlap.x) < fabsf(overlap.y))
  {
    std::cout << "empurrando em x ";
    a->setPosition(a->getPosition().x - overlap.x, a->getPosition().y);
    // b->setPosition(b->getPosition().x + overlap.x, b->getPosition().y);
  }
  else
  {
    std::cout << "empurrando em y ";
    a->setPosition(a->getPosition().x, a->getPosition().y - overlap.y);
    // b->setPosition(b->getPosition().x, b->getPosition().y + overlap.y);
  }
}

void PhysicsSystem::resolveCollision(GameObject *a, GameObject *b, Vector2f overlap)
{
  // colisao de spell
  if (a->getSpell() != nullptr)
  {
    resolveSpellCollision(a, b, overlap);
  }
  else if (b->getSpell() != nullptr)
  {
    resolveSpellCollision(b, a, overlap);
  }
  // colisao de fisica
  if (
      a->getPhysics()->getIsIntangible() ||
      b->getPhysics()->getIsIntangible())
  {
    return;
  }
  else if (a->getPhysics()->getIsUnstoppable() || b->getPhysics()->getIsUnstoppable())
  {
    resolveImmovableObjectCollision(a, b, overlap);
  }
  else
  {
    std::cout << "Resolve spell" << std::endl;
    resolveObjectsCollision(a, b, overlap);
  }
}

void PhysicsSystem::resolveSpellCollision(GameObject *spell, GameObject *target, Vector2f overlap)
{
  // std::cout << "resolving spell collision" << std::endl;
  spell->getSpell()->onCollision(spell, target, overlap);
}
