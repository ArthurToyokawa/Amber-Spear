#include "gameObject.hpp"
#include "textureManager.hpp"

#include <iostream>

GameObject::GameObject(float startingX, float startingY)
{
  alive = true;
  pos.set((float)startingX, (float)startingY);
}

void GameObject::updatePhysics(float time)
{
  pos = physics->update(time, pos);
}

void GameObject::updatePosition()
{
  sprite->update(pos);
}
