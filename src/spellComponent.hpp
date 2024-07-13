#pragma once
#include <iostream>
#include <functional> 

class SpellComponent
{
public:
    void initSpell(std::function<void()> onCastFunc, std::function<void()> onCollisionFunc)
    {
      if (onCastFunc) {
        onCastFunc();
      }
    }
    std::function<void()> onCollision;

private:
};
