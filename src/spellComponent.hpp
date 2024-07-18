#pragma once
#include <iostream>
#include <functional>

class SpellComponent
{
public:
  SpellComponent(std::function<void()> onCastFunc, std::function<void()> onCollisionFunc)
  {
    if (onCastFunc)
    {
      onCastFunc();
    }
    onCollision = onCollisionFunc;
  }
  std::function<void()> onCollision;

private:
};
