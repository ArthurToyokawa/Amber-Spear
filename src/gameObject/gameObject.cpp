#include <iostream>

#include "gameObject.hpp"

GameObject::GameObject(float startingX, float startingY)
{
  alive = true;
  pos.set(startingX, startingY);
}

void GameObject::kill()
{
  alive = false;
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
