#include "gameObject.hpp"
#include "textureManager.hpp"
#include "entityManager.hpp"

#include <iostream>

GameObject::GameObject(EntityManager *e, float startingX, float startingY)
{
  alive = true;
  pos.set(startingX, startingY);
}

void GameObject::updatePhysics(float time)
{
  pos = physics->update(time, pos);
}

void GameObject::updatePosition()
{
  sprite->update(pos);
}
