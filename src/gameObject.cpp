#include "gameObject.hpp"
#include "entityManager.hpp"

#include <iostream>

GameObject::GameObject(EntityManager *e, float startingX, float startingY)
{
  alive = true;
  pos.set(startingX, startingY);
  entityManager = e;
}

void GameObject::kill()
{
  alive = false;
  if (pointsOnDeath != 0)
  {
    entityManager->getPointCounter()->addPoints(pointsOnDeath);
  }
}

void GameObject::updatePhysics(float time)
{
  if (physics != nullptr)
  {
    pos = physics->update(time, pos);
  }
}

void GameObject::updateSprite()
{
  if (sprite != nullptr)
  {
    sprite->update(pos);
  }
}
