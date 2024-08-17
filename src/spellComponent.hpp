#pragma once
#include <iostream>
#include <functional>

class GameObject;

class SpellComponent
{
public:
  SpellComponent(std::function<void()> onCastFunc, std::function<void(GameObject *spell, GameObject *target, Vector2f overlap)> onCollisionFunc)
  {
    if (onCastFunc)
    {
      onCastFunc();
    }
    onCollision = onCollisionFunc;
  }
  std::function<void(GameObject *spell, GameObject *target, Vector2f overlap)> onCollision;

private:
};
