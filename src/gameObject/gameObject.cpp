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

void GameObject::updateAuras(float time)
{
  if (!auras.empty())
  {
    for (auto it = auras.begin(); it != auras.end();)
    {
      auto aura = *it;
      aura->update(time);
      // std::cout << "Updating aura" << aura->getTimeRemaining() << std::endl;

      if (aura->getTimeRemaining() <= 0.0)
      {
        std::cout << "Killing Aura" << std::endl;
        aura->callOnEnd();
        delete aura;
        it = auras.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }
}
